#!/usr/local/bin/python3

import sys
import argparse
import project_configuration as config
from neighbor_parser import Parser
from flow import Flow
from scheduling_configuration import Scheduling_algorithm, Scheduling_strategies, Scheduling_window_size_algorithm
from scheduling import Schedule
from scheduling_contiki import Contiki_schedule

def main():
  parser = argparse.ArgumentParser(description='Scheduler')
  parser.add_argument('-dir', '--folder', help='Folder containing neighbor discovery statistics', required=True)
  parser.add_argument('-f', '--file', help='File in specified folder, include iff 1 file')
  parser.add_argument('-flows_f', '--flows_file', help='File of comma seperated values with to be scheduled flows, lower priority than --flows')
  parser.add_argument('-flows', '--flows', help='String of to be scheduled flows; "<from>,<to>[,<release_time>[,<deadline>]];...", default: 1,2')
  parser.add_argument('-tb', '--testbed', help='Testbed, default: cooja', choices=['cooja', 'flocklab', 'kiel'])
  parser.add_argument('-n_cooja', '--num_cooja_nodes', help='Number of cooja nodes, default: 5', type=int)
  parser.add_argument('-trg', '--target', help='Target platform, default: sky', choices=['zoul', 'sky', 'cooja'])
  parser.add_argument('-alg', '--algorithm', help='Scheduling algorithm, default: R-LPF', choices=['rlpf'])
  parser.add_argument('-strat', '--strategy', help='(Re)Transmission strategy, default: sliding', choices=['no', 'slot', 'sliding'])
  parser.add_argument('-salg', '--sliding_algorithm', help='Sliding Windows algorithm, default: etx_link_based',
                      choices=['etx_based', 'etx_based_doubled', 'etx_based_trippled',
                               'etx_link_based', 'etx_link_based_doubled', 'etx_link_based_trippled', 'fixed']
                     )
  parser.add_argument('-wsize', '--fixed_window_size', help="Fixed window size for sliding algorithm 'fixed' (minimum = 2), default: 5", type=int)
  parser.add_argument('-etx', '--etx_power', help='ETX-Power, default: 2', type=int, choices=[1, 2, 3])
  parser.add_argument('-ch', '--channels', help='Number channels, default: 4', type=int, choices=range(1,17))
  parser.add_argument('-m_etx', '--max_etx', help='Maximal accepted ETX value, default: 10', type=int)
  parser.add_argument('-with_cs', '--with_contiki_schedule', help='Generate Contiki Schedule, default: False', action='store_true')
  parser.add_argument('-ts', '--timesource', help='Time Source node of network, default: 1', type=int)
  parser.add_argument('-out', '--output_file', help='Output File of Contiki Schedule')
  parser.add_argument('-m_len', '--minimal_length', help='Minimal Schedule Length, default: minimal possible', type=int)
  parser.add_argument('-with_ts', '--with_scheduled_timesource', help='Schedule timesource for each node, default: False', action='store_true')
  parser.add_argument('-p_etx', '--print_etx', help='Print ETX table', action='store_true')
  parser.add_argument('-p_prr', '--print_prr', help='Print PRR table', action='store_true')
  parser.add_argument('-p_rssi', '--print_rssi', help='Print RSSI table', action='store_true')
  parser.add_argument('-p_sched', '--print_schedule', help='Print Schedule', action='store_true')
  args = parser.parse_args()

  folder = args.folder
  fixed_window_size = None

  if args.file:
    filename = args.file

  if args.testbed:
    if args.testbed == 'cooja':
      testbed = config.Testbed.cooja
    elif args.testbed == 'flocklab':
      testbed = config.Testbed.flocklab
    elif args.testbed == 'kiel':
      testbed = config.Testbed.kiel
  else:
    testbed = config.Testbed.cooja

  if testbed == config.Testbed.cooja:
    if args.num_cooja_nodes:
      num_cooja_nodes = args.num_cooja_nodes
    else:
      num_cooja_nodes = 5
    node_ids = config.get_valid_node_ids(testbed, num_cooja_nodes)
  else:
    node_ids = config.get_valid_node_ids(testbed)

  if args.target:
    if args.target == 'zoul':
      target = config.Platform.zoul
    elif args.target == 'sky':
      target = config.Platform.sky
    elif args.target == 'cooja':
      target = config.Platform.cooja
  else:
    target = config.Platform.sky
  
  if args.algorithm:
    if args.algorithm == 'rlpf':
      scheduling_algorithm = Scheduling_algorithm.rlpf
  else:
    scheduling_algorithm = Scheduling_algorithm.rlpf

  if args.strategy:
    if args.strategy == 'no':
      scheduling_strategy = Scheduling_strategies.no_retransmissions
    elif args.strategy == 'slot':
      scheduling_strategy = Scheduling_strategies.upper_etx_tx_per_link
    elif args.strategy == 'sliding':
      scheduling_strategy = Scheduling_strategies.sliding_window
  else:
    scheduling_strategy = Scheduling_strategies.sliding_window

  if args.sliding_algorithm:
    if args.sliding_algorithm == 'etx_based':
      scheduling_window_size_alg = Scheduling_window_size_algorithm.etx_based
    elif args.sliding_algorithm == 'etx_based_doubled':
      scheduling_window_size_alg = Scheduling_window_size_algorithm.etx_based_doubled
    elif args.sliding_algorithm == 'etx_based_trippled':
      scheduling_window_size_alg = Scheduling_window_size_algorithm.etx_based_trippled
    elif args.sliding_algorithm == 'etx_link_based':
      scheduling_window_size_alg = Scheduling_window_size_algorithm.etx_link_based
    elif args.sliding_algorithm == 'etx_link_based_doubled':
      scheduling_window_size_alg = Scheduling_window_size_algorithm.etx_link_based_doubled
    elif args.sliding_algorithm == 'etx_link_based_trippled':
      scheduling_window_size_alg = Scheduling_window_size_algorithm.etx_link_based_trippled
    elif args.sliding_algorithm == 'fixed':
      scheduling_window_size_alg = Scheduling_window_size_algorithm.fixed
      if args.fixed_window_size:
        if args.fixed_window_size < 2:
          raise argparse.ArgumentTypeError("Minimum window size is 2")
        else:
          fixed_window_size = args.fixed_window_size
      else:
        fixed_window_size = 5
  else:
    scheduling_window_size_alg = Scheduling_window_size_algorithm.etx_link_based

  if args.etx_power:
    etx_power = args.etx_power
  else:
    etx_power = 2

  if args.channels:
    num_channels = args.channels
  else:
    num_channels = 4

  if args.max_etx:
    max_etx = args.max_etx
  else:
    max_etx = 10

  if args.with_contiki_schedule:
    generate_contiki_schedule = True
    if args.output_file:
      contiki_output_file = args.output_file
    else:
      raise ValueError("Please specify the Contiki output file!")

    if args.minimal_length:
      contiki_minimal_schedule_length = args.minimal_length
    else:
      contiki_minimal_schedule_length = 0

    if args.with_scheduled_timesource:
      contiki_schedule_timesource = True
    else:
      contiki_schedule_timesource = False
  else:
    generate_contiki_schedule = False

  if args.timesource and args.timesource in node_ids:
    network_time_source = args.timesource
  else:
    network_time_source = 1

  communications = []
  if args.flows:
    flows_to_create = args.flows.split(';')
    for flow_to_create in flows_to_create:
      flow_parameters = [int(x.strip()) for x in flow_to_create.split(',')]
      communications.append(tuple(flow_parameters[:4]))
  elif args.flows_file:
    with open(args.flows_file) as flows_file:
      for line in flows_file:
        flow_parameters = [int(x.strip()) for x in line.split(',')]
        communications.append(tuple(flow_parameters[:4]))
  else:
    communications.append( (1, 2) )

  
  # Parse neighbor discovery file(s)
  neighbor_parser = Parser(node_ids, folder, filename, max_etx)
  neighbor_parser.parse_neighbor_data(args.print_etx, args.print_prr, args.print_rssi)

  flows = []

  for flow_id, communication in enumerate(communications):
    source = communication[0]
    destination = communication[1]
    if len(communication) > 2:
      release_time = communication[2]
    else:
      release_time = 0
    if len(communication) > 3:
      deadline = communication[3]
    else:
      deadline = None
    flows.append(Flow(neighbor_parser.graph_etx, flow_id+1, source, destination, release_time, deadline)) # , max_sub_flow_length)
  
  schedule = Schedule(flows) # parser.graph_etx, 
  schedule.create(etx_power, num_channels, scheduling_algorithm, scheduling_strategy, scheduling_window_size_alg, fixed_window_size)

  if args.print_schedule:
    print(schedule)

  if generate_contiki_schedule:
    contiki_schedule = Contiki_schedule(neighbor_parser.graph_etx, schedule, node_ids, network_time_source)
    contiki_schedule.generate(contiki_output_file, contiki_minimal_schedule_length, contiki_schedule_timesource)


if __name__ == "__main__":
  main()
