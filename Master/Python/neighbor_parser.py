#!/usr/local/bin/python3
import os
from re import search as re_search
from enum import Enum

class Data_table(Enum):
  etx = 0
  prr = 1
  rssi = 2

class Parser(object):

  def __init__(self, valid_node_ids, folder_path, filename=None, max_etx_bound=None, min_rssi_bound=None):
    self.valid_node_ids = valid_node_ids
    if folder_path[-1] == '/':
      self.folder = folder_path
    else:
      self.folder = folder_path + '/'
    self.filename = filename
    self.max_etx_bound = max_etx_bound
    self.min_rssi_bound = min_rssi_bound
    self.parse_graphs = []

  def add_to_parse_graph(self, number, sender, receiver=0, rssi=0):
    if sender not in self.parse_graphs[-1]:
      self.parse_graphs[-1][sender] = {}
    if receiver:
        if receiver not in self.parse_graphs[-1][sender]:
            self.parse_graphs[-1][sender][receiver] = []
        self.parse_graphs[-1][sender][receiver].append((number, rssi))
    else:
        if sender not in self.parse_graphs[-1][sender]:
            self.parse_graphs[-1][sender][sender] = []
        self.parse_graphs[-1][sender][sender].append(number)

  def match_neighbor_data(self, line):
    match = re_search(r'rcvd;(\d+);(\d+);(\d+);(\d+);(-?\d+)', line)                      # rcvd;<node_id>;<sender>;<channel>;<number>;<rssi>
    if match:
      packet_number = int(match.group(4))
      sender        = int(match.group(2))
      receiver      = int(match.group(1)) # == node_id
      rssi          = int(match.group(5))
      # channel     = int(match.group(3)) # currently unused, but can be used for channel statistics

      if receiver in self.valid_node_ids and sender in self.valid_node_ids:
        self.add_to_parse_graph(packet_number, sender, receiver, rssi)
      
    else:
      match = re_search(r'sent;(\d+);(\d+)', line)                                        # sent;<node_id>;<number>
      if match:
        packet_number = int(match.group(2))
        sender        = int(match.group(1))

        if sender in self.valid_node_ids:
          self.add_to_parse_graph(packet_number, sender)


  def parse_file(self, filepath):
    print(filepath)
    with open(filepath, encoding="utf8", errors='ignore') as f:
      self.parse_graphs.append({})
      for line in f:
        self.match_neighbor_data(line)

  def combine_parse_graphs(self):
    self.graph_etx = {}
    self.graph_prr = {}
    self.graph_rssi = {}

    for sender in self.valid_node_ids:
      self.graph_etx[sender] = {}
      self.graph_prr[sender] = {}
      self.graph_rssi[sender] = {}
      highest_received_number = []
      received_packets_count = []

      for parse_graph in self.parse_graphs:
        received_packets_count.append({})

        if sender in [*parse_graph]:
          highest_received_number.append(0)
          for receiver in [*parse_graph[sender]]:
            if receiver != sender:
              last_received_packet_number = parse_graph[sender][receiver][-1][0]
              if last_received_packet_number > highest_received_number[-1]:
                highest_received_number[-1] = last_received_packet_number
              received_packets_count[-1][receiver] = len(parse_graph[sender][receiver])

      # if sender exists anywhere:
      if sum(highest_received_number):
        total_number_receivable_packets = float(sum(highest_received_number))
        for receiver in self.valid_node_ids:
          if receiver != sender:
            total_received_packets_count = 0
            sums_rssi = []
            for idx in range(len(received_packets_count)):
              if receiver in [*received_packets_count[idx]]:
                total_received_packets_count += received_packets_count[idx][receiver]

              # rssi calc
              if (sender in [*self.parse_graphs[idx]]) and (receiver in [*self.parse_graphs[idx][sender]]):
                sums_rssi.append(sum(rssi for _, rssi in self.parse_graphs[idx][sender][receiver])) # [(n, r), (n, r), ...]
            if total_received_packets_count > 0:
              prr = float(total_received_packets_count) / total_number_receivable_packets
              etx = total_number_receivable_packets / float(total_received_packets_count)
              if (not self.max_etx_bound) or (etx < self.max_etx_bound):
                self.graph_prr[sender][receiver] = prr
                self.graph_etx[sender][receiver] = etx
              
              # rssi calc
              avg_rssi_value = float(sum(sums_rssi)) / float(total_received_packets_count)
              if (not self.min_rssi_bound) or (avg_rssi_value > self.min_rssi_bound):
                self.graph_rssi[sender][receiver] = avg_rssi_value

  def print_parsed_data_table(self, table_type):
    if table_type == Data_table.etx:
      output = 'ETX'
      graph = self.graph_etx
      entry_format_string = '{:8.3f}'
    elif table_type == Data_table.prr:
      output = 'PRR'
      graph = self.graph_prr
      entry_format_string = '{:8.3f}'
    elif table_type == Data_table.rssi:
      output = 'RSSI'
      graph = self.graph_rssi
      entry_format_string = '{:8.1f}'

    output += ' table:\n^^^^^^^^^^\nr\\f'
    for sender in self.valid_node_ids:
      output += '{:8d}'.format(sender)
    output += '\n'
    for receiver in self.valid_node_ids:
      output += '{:3d}'.format(receiver)
      for sender in self.valid_node_ids:
        if sender in graph:
          receiver_ids = [*graph[sender]]
          if receiver in receiver_ids:
            output += entry_format_string.format(graph[sender][receiver])
          else:
            output += '        '
      output += '\n'
    print(output)


  def parse_neighbor_data(self, print_etx=False, print_prr=False, print_rssi=False):
    if self.filename:
      self.parse_file(self.folder + self.filename)
    else:
      for filename in os.listdir(self.folder):
        self.parse_file(self.folder + filename)
    self.combine_parse_graphs()
    if print_prr:
      self.print_parsed_data_table(Data_table.prr)
    if print_etx:
      self.print_parsed_data_table(Data_table.etx)
    if print_rssi:
      self.print_parsed_data_table(Data_table.rssi)
