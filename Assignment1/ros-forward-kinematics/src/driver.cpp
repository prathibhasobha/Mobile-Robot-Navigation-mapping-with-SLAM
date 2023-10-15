// This program publishes random velocity commands, using
// a maximum linear velocity read from a parameter.
// rosparam set /publish_velocity/max_vel 0.1
// rosrun turtlesim_cleaner pubvel_with_max _max_vel:=1
#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <stdlib.h>

int main(int argc, char **argv) {
  ros::init(argc, argv, "publish_velocity");
  ros::NodeHandle nh;
  ros::Publisher pub = nh.advertise<geometry_msgs::Twist>(
      "cmd_vel", 1);
  srand(time(0));

  ros::Rate rate(2);
  while(ros::ok()) {
    // Create and send a random velocity command.
    geometry_msgs::Twist msg;
    msg.linear.x = double(rand())/double(RAND_MAX);
    msg.angular.z = 2*double(rand())/double(RAND_MAX)-1;
    pub.publish(msg);
ROS_INFO_STREAM("Sending cmd_vel"
<< " LINEAR=" << msg.linear.x
<< " ANGULAR=" << msg.angular.z);

    // Wait until it's time for another iteration.
    rate.sleep();
  }
}
