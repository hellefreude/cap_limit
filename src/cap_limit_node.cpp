#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <ros/ros.h>
#include <sensor_msgs/Range.h>
#include <wiringPi.h>

using namespace std;

namespace cap_limit_node {

class Limit {
 public:
  Limit(int m1, int m2) : spdpin_(m1), toqpin_(m2) {
    pinMode(spdpin_, INPUT);
    pinMode(toqpin_, INPUT);
  }

  int mode(int* mode, bool* err) {

    if (digitalRead(spdpin_) == HIGH) {
      *mode = 1;
      *err = false;
      return *mode;
    }

    else if (digitalRead(toqpin_) == HIGH) {
      *mode = 2;
      *err = false;
      return *mode;
    }

    else if ((digitalRead(spdpin_) == LOW) && digitalRead(toqpin_) == LOW ) {
      *mode = 0;
      *err = false;
      return *mode;
    }

    else {
      *mode = 0;
      *err = true;
      return 0;
    }
  }

private:
  int spdpin_;
  int toqpin_;
};

} // namespace cap_limit_node

int main(int argc, char **argv) {

  // Start ROS node.
  ROS_INFO("Starting node");
  ros::init(argc, argv, "limit_sensor");
  ros::NodeHandle node;
  ros::Rate rate(10);  // 10 hz

  // Build N sonars.
  wiringPiSetupSys();  // uses gpio pin numbering
  // TODO: config these
  vector<cap_limit_node::Limit> limits;
  limits.push_back(cap_limit_node::Limit(23, 25));
 
  // Build a publisher for each sonar.
  vector<ros::Publisher> limit_pubs;
  for (int i = 0; i < limits.size(); ++i) {
    stringstream ss;
    ss << "limit_" << i;
    limit_pubs.push_back(node.advertise<sensor_msgs::Range>(ss.str(), 10));
  }
  
  // Build base range message that will be used for
  // each time a msg is published.
  sensor_msgs::Range range;
 
  while(ros::ok()) {
    for (int i = 0; i < limits.size(); ++i) {    
    limit_pubs[i].publish(range);
    ros::spinOnce();
    rate.sleep();
   }    
  }
  return 0;
}
