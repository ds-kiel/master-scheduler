#!/usr/local/bin/python3
from scheduling_configuration import Scheduling_algorithm, Scheduling_strategies, Scheduling_window_size_algorithm
from flow import Flow
from cell import Cell

class Schedule(object):

  def __init__(self, flows): # , graph
    # self.graph = graph  # Dict{sender:Dict{receiver:etx}}
    self.flows = flows  # List[Flow]
    

  def order_flows_decreasing(self):
    self.flows.sort(key=lambda x: x.length, reverse=True)

  def available_channel_in_slot(self, slot_index):
    for channel_idx in range(len(self.schedule)):
      if self.schedule[channel_idx][slot_index] == 0:
        return channel_idx
    return False

  def schedulable_in_slot(self, slot_index, participants):
    slot_available = False
    for channel in self.schedule:
      if channel[slot_index] == 0:
        slot_available = True
    if not slot_available:
      return False
    if len(self.used_nodes_in_timeslot[slot_index]) == 0: # no participant in slot
      return True
    for participant in participants:
      if participant in self.used_nodes_in_timeslot[slot_index]:
        return False
    return True

  def create(self, etx_power, num_channels, algorithm, strategy, window_size_algorithm=None, fixed_window_size=None):
    for flow in self.flows:
      flow.compute_path(etx_power)
    #   flow.modify_path(strategy, window_size)

    self.num_channels = num_channels
    self.strategy = strategy

    max_schedule_length = 0
    for flow in self.flows:
      flow.create_cells(strategy, window_size_algorithm, fixed_window_size)
      max_schedule_length += flow.length
    
    # init schedule
    self.schedule = [[0] * max_schedule_length for _ in range(num_channels)]
    self.used_nodes_in_timeslot = [[] for _ in range(max_schedule_length)]

    if algorithm == Scheduling_algorithm.rlpf:
      last_timeslot = 0
      self.order_flows_decreasing()
      for flow in self.flows:
        # last_index = -1
        insert_at_index = 0
        for cell in reversed(flow.cells):
          while not self.schedulable_in_slot(insert_at_index, cell.participants):
            insert_at_index += 1
          channel = self.available_channel_in_slot(insert_at_index)
          self.schedule[channel][insert_at_index] = cell
          self.used_nodes_in_timeslot[insert_at_index].extend(cell.participants)
          if insert_at_index > last_timeslot:
            last_timeslot = insert_at_index

      # remove unused cells at end
      for channel_idx, channel in enumerate(self.schedule):
        self.schedule[channel_idx] = channel[:last_timeslot+1]
        for timeslot in range(len(self.schedule[channel_idx])//2):
          tmp_timeslot_cell = self.schedule[channel_idx][timeslot]
          self.schedule[channel_idx][timeslot] = self.schedule[channel_idx][last_timeslot-timeslot]
          self.schedule[channel_idx][last_timeslot-timeslot] = tmp_timeslot_cell
        # set cell attributes
        for timeslot in range(last_timeslot+1):
          cell = self.schedule[channel_idx][timeslot]
          if isinstance(cell, Cell):
            cell.set_schedule_attributes(timeslot, channel_idx)

  def get_node_schedule(self, *nodes):
    # returns schedule for each node
    node_schedule = {}
    for timeslot in range(len(self.schedule[0])):
      for channel in range(len(self.schedule)):
        cell = self.schedule[channel][timeslot]
        if isinstance(cell, Cell):
          for participant in cell.participants:
            if participant in nodes:
              if participant not in node_schedule:
                node_schedule[participant] = []
              node_schedule[participant].append(cell)
    return node_schedule

  def get_max_cell_participants(self):
    max_num_cell_participants = 0
    for timeslot in range(len(self.schedule[0])):
      for channel in range(len(self.schedule)):
        cell = self.schedule[channel][timeslot]
        if isinstance(cell, Cell):
          num_participants = len(cell.participants)
          if num_participants > max_num_cell_participants:
            max_num_cell_participants = num_participants
    return max_num_cell_participants

  def get_flow_from_id(self, id):
    for flow in self.flows:
      if id == flow.flow_number:
        return flow
    return False

  def __str__(self):
    string = "Scheduling strategy: {}\n"
    separator = " | "
    # cell_character_width = len("nn -> nn (nn -> nn)")
    cell_character_width = 19
    if self.strategy == Scheduling_strategies.no_retransmissions:
      string = string.format("no retransmissions")
    elif self.strategy == Scheduling_strategies.upper_etx_tx_per_link:
      string = string.format("slot-based upper etx")
    elif self.strategy == Scheduling_strategies.sliding_window:
      string = string.format("sliding windows")
      max_num_cell_participants = self.get_max_cell_participants()
      # cell_character_width = len("nn, ") * max_num_cell_participants - len(",") + len("(nn -> nn)")
      cell_character_width = 4 * max_num_cell_participants - 1 + 10
      empty_participant = "    " # "nn, "
    else:
      string.format("unknown")
    
    # line_separator = (len("nnn | ") + (cell_character_width + len(" | ")) * self.num_channels - len(" ")) * "-" + "\n"
    line_separator = (6 + (cell_character_width + 3) * self.num_channels - 1) * "-" + "\n"
    empty = " " * cell_character_width

    for timeslot in range(len(self.schedule[0])):
      string += line_separator
      string += str(timeslot).rjust(3) + separator
      for channel in range(len(self.schedule)):
        cell = self.schedule[channel][timeslot]
        if not isinstance(cell, Cell):
          string += empty
        else:
          if self.strategy == Scheduling_strategies.sliding_window:
            string += ', '.join(str(participant).rjust(2) for participant in cell.participants)
            string += ' '
            num_participants = len(cell.participants)
            string += empty_participant * (max_num_cell_participants - num_participants)
          else:
            sender = cell.participants[0]
            receiver = cell.participants[-1]
            string += "{} -> {}".format(str(sender).rjust(2), str(receiver).rjust(2))
          flow = self.get_flow_from_id(cell.flow_number)
          string += "({} -> {})".format(str(flow.source).rjust(2), str(flow.destination).rjust(2))
        string += separator
      string += "\n"
    string += line_separator
    return string
          

    
