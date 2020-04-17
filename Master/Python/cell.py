#!/usr/local/bin/python3

class Cell(object):

  def __init__(self, flow_number, *participants):
    self.flow_number = flow_number
    self.participants = participants

  def set_schedule_attributes(self, timeslot, channel_offset):
    self.timeslot = timeslot
    self.channel = channel_offset

  def __str__(self):
    string = "TS: {}, channel: {} - Flow: {}, Nodes: ".format(str(self.timeslot).rjust(2), str(self.channel).rjust(2), str(self.flow_number).rjust(2))
    for p in self.participants:
      string += str(p) + ", "
    return string
