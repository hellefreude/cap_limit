#!/usr/bin/env python
import rospy
from sensor_msgs.msg import Range

limits = [0, 0, 0]
lkg_limits = [0, 0, 0]

def callback(msg, idx):
  global limits

  limits[idx] = msg.range

  if lkg_limits[idx] == 0 or msg.range != 30.0:
    lkg_limits[idx] = msg.range
      
rospy.init_node('limit_subscriber')

for i in range(2):
  rospy.Subscriber("/robotZero/limit_%d" % i, Range,
                   callback, i)

r = rospy.Rate(5)

while not rospy.is_shutdown():
  s = ["%5.2f" % v for v in limits]
  s += ["%5.2f" % v for v in lkg_limits]
  print " ".join(s)
  r.sleep()
                      
