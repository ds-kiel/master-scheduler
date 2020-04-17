#!/usr/local/bin/python3

from enum import Enum

class Scheduling_strategies(Enum):
    no_retransmissions = 0
    upper_etx_tx_per_link = 1
    sliding_window = 2
    # multiple_tx_per_link = 3 # currently 3 TX per link

class Scheduling_algorithm(Enum):
    rlpf = 0 # reverse longest path first

class Scheduling_window_size_algorithm(Enum):
  etx_based = 0
  etx_based_doubled = 1
  etx_based_trippled = 2
  etx_link_based = 3
  etx_link_based_doubled = 4
  etx_link_based_trippled = 5
  fixed = 6
