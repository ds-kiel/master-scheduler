#!/usr/local/bin/python3
import copy
import dijkstra
import math
from scheduling_configuration import Scheduling_strategies, Scheduling_window_size_algorithm
from cell import Cell

class Flow(object):
  
  def __init__(self, graph, flow_id, source, destination, release_time=0, deadline=None, max_sub_flow_length=10): #ID
    self.graph = graph
    self.flow_number = flow_id
    self.source = source
    self.destination = destination
    self.release_time = release_time
    self.deadline = deadline
    self.max_sub_flow_length = max_sub_flow_length

  def compute_path(self, etx_power):
    etx_graph = copy.deepcopy(self.graph)
    for sender, receivers in etx_graph.items():
      for receiver in [*receivers]:
        weight = etx_graph[sender][receiver]
        etx_graph[sender][receiver] = weight ** etx_power

    _, path = dijkstra.shortestPath(etx_graph, self.source, self.destination)
    self.length = len(path)

    # overlapping sub-flows for too long single flows
    if self.length > self.max_sub_flow_length:
      num_sub_flows = 2
      while math.ceil(self.length / num_sub_flows) > self.max_sub_flow_length - 1: # - 1: last element of previous subflow has to be included
        num_sub_flows += 1
      sub_flow_length = math.ceil(self.length / num_sub_flows)
    else:
      num_sub_flows = 1
      sub_flow_length = self.length
    sub_flow_paths = {}
    sub_flow_paths[0] = path[0:sub_flow_length]
    for idx in range(1, num_sub_flows):
      sub_flow_paths[idx] = path[idx*sub_flow_length-1:idx*sub_flow_length+sub_flow_length] # include last elment of previous sub-flow
    self.path = sub_flow_paths

     # split cost into subflows
    self.cost = {}
    for sub_path_idx, sub_path in self.path.items():
      sub_path_length = len(sub_path)
      sub_path_cost = 0
      for idx in range(sub_path_length - 1):
        hop_sender = sub_path[idx]
        hop_receiver = sub_path[idx + 1]
        sub_path_cost += self.graph[hop_sender][hop_receiver]
      self.cost[sub_path_idx] = sub_path_cost


  def calculate_window_size(self, sub_path_index, window_size_algorithm, fixed_window_size):
    self.window_size = {}
    if fixed_window_size:
      if fixed_window_size < 2:
        raise ValueError("Non supported window size given")
      else:
        self.window_size[sub_path_index] = fixed_window_size
      return

    sub_path = self.path[sub_path_index]
    sub_path_cost = self.cost[sub_path_index]
    hop_count = len(sub_path) - 1

    # calculate cost
    if window_size_algorithm == Scheduling_window_size_algorithm.etx_based:
      cost = math.ceil(sub_path_cost)
    elif window_size_algorithm == Scheduling_window_size_algorithm.etx_based_doubled:
      cost = math.ceil(2 * sub_path_cost)
    elif window_size_algorithm == Scheduling_window_size_algorithm.etx_based_trippled:
      cost = math.ceil(3 * sub_path_cost)
    elif window_size_algorithm == Scheduling_window_size_algorithm.etx_link_based or \
         window_size_algorithm == Scheduling_window_size_algorithm.etx_link_based_doubled or \
         window_size_algorithm == Scheduling_window_size_algorithm.etx_link_based_trippled:
      cost = 0
      for hop_idx in range(hop_count):
        hop_sender = sub_path[hop_idx]
        hop_receiver = sub_path[hop_idx + 1]
        hop_etx_cost = math.ceil(self.graph[hop_sender][hop_receiver])
        cost += hop_etx_cost

    # calculate window size
    if window_size_algorithm == Scheduling_window_size_algorithm.etx_based or \
       window_size_algorithm == Scheduling_window_size_algorithm.etx_based_doubled or \
       window_size_algorithm == Scheduling_window_size_algorithm.etx_based_trippled:
      self.window_size[sub_path_index] = cost - hop_count + 2
    elif window_size_algorithm == Scheduling_window_size_algorithm.etx_link_based:
      self.window_size[sub_path_index] = cost - hop_count + 2
    elif window_size_algorithm == Scheduling_window_size_algorithm.etx_link_based_doubled:
      self.window_size[sub_path_index] = 2*cost - hop_count + 2
    elif window_size_algorithm == Scheduling_window_size_algorithm.etx_link_based_trippled:
      self.window_size[sub_path_index] = 3*cost - hop_count + 2

  def create_cells(self, strategy, window_size_algorithm=None, fixed_window_size=None):
    self.cells = []
    if not hasattr(self, 'path'):
      raise RuntimeError("Flow: no path was calculated yet")

    self.max_transmissions = {}
    for sub_path_idx, sub_path in self.path.items():
      hop_count = len(sub_path) - 1
      if strategy == Scheduling_strategies.no_retransmissions:
        for hop_idx in range(hop_count):
          hop_sender = sub_path[hop_idx]
          hop_receiver = sub_path[hop_idx + 1]
          self.cells.append(Cell(self.flow_number, hop_sender, hop_receiver))
          self.max_transmissions[hop_sender] = 1
      elif strategy == Scheduling_strategies.upper_etx_tx_per_link:
        for hop_idx in range(hop_count):
          hop_sender = sub_path[hop_idx]
          hop_receiver = sub_path[hop_idx + 1]
          hop_etx_ceil = math.ceil(self.graph[hop_sender][hop_receiver])
          for _ in range(hop_etx_ceil):
            self.cells.append(Cell(self.flow_number, hop_sender, hop_receiver))
          self.max_transmissions[hop_sender] = hop_etx_ceil
      elif strategy == Scheduling_strategies.sliding_window:
        self.calculate_window_size(sub_path_idx, window_size_algorithm, fixed_window_size)
        sub_path_window_size = self.window_size[sub_path_idx]
        num_slots = hop_count + sub_path_window_size - 2
        participant_lists = [[] for _ in range(num_slots)]
        for path_idx, participant in enumerate(sub_path):
          if path_idx == 0:                                                 # first element
            insertion_indices = range(sub_path_window_size - 1)
            self.max_transmissions[participant] = len(insertion_indices)
          elif path_idx == len(sub_path) - 1:                              # last element (receiver)
            insertion_indices = range(path_idx-1, path_idx + sub_path_window_size - 2)
          else:                                                             # other elements
            insertion_indices = range(path_idx-1, path_idx + sub_path_window_size - 1)
            self.max_transmissions[participant] = len(insertion_indices) - 1 # only possible sending slots
          for insertion_idx in insertion_indices:
            participant_lists[insertion_idx].append(participant)
        for participants in participant_lists:
          self.cells.append(Cell(self.flow_number, *participants))
    self.length = len(self.cells)


  def output_flow_path(self):
    output = ""
    for sub_path in self.path:
      for node in sub_path:
        output += str(node) + ";"
    output = output[:-1] + "\n"
    return output

  def get_timeslots_of_source(self):
    timeslots = []
    for cell in self.cells:
      if self.source in cell.participants:
        timeslots.append(cell.timeslot)
    return timeslots
