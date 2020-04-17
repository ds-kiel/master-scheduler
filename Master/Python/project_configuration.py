#!/usr/local/bin/python3
from enum import Enum

class Testbed(Enum):
  cooja = 0
  flocklab = 1
  kiel = 2

class Platform(Enum):
  zoul = 0
  sky = 1
  cooja = 2

def get_valid_node_ids(testbed, cooja_node_count=5):
  if testbed == Testbed.flocklab:
    valid_node_ids = [ 1,  2,  3,  4,  6,  7,  8, 10,
                      11, 13, 14, 15, 16, 17, 18, 19, 20,
                      22, 23, 24, 25, 26, 27, 28,
                      31, 32, 33]
  elif testbed == Testbed.kiel:
    valid_node_ids = [ 1,  2,  3,  4,  5,  6,  7,  8,  9, 10,
                      12, 13, 14, 15, 16, 17, 18, 19, 20, 21]
  elif testbed == Testbed.cooja:
    valid_node_ids = [i for i in range(1, cooja_node_count+1)]
  return valid_node_ids
