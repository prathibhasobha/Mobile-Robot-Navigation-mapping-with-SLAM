// Include necessary ROS and geometry_msgs headers

#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <stdlib.h>

// Main function

int main(int argc, char **argv) {

//Initialize the ROS node

  ros::init(argc, argv, "publish_velocity");

//Create a ROS NodeHsandle to communicate with ROS system

  ros::NodeHandle nh;

//Create a publisher that publishes the message of the type geometry_msgs::Twist to the topic "cmd_vel" with a buffer size of 1 

  ros::Publisher pub = nh.advertise<geometry_msgs::Twist>("cmd_vel", 1);
  srand(time(0));

//set the loop rate to 2 Hz.

  ros::Rate rate(2);

// Main loop

  while(ros::ok()) {

// Create and send a random velocity command.

    geometry_msgs::Twist msg;

//set linera velocity to a random value between 0 and 1

    msg.linear.x = double(rand())/double(RAND_MAX);

//Set angular velocity to a random value between -1 and 1

    msg.angular.z = 2*double(rand())/double(RAND_MAX)-1;

//publish the random velocity command.

    pub.publish(msg);

//Log the sent velocity command to the console.

ROS_INFO_STREAM("Sending cmd_vel"
<< " LINEAR=" << msg.linear.x
<< " ANGULAR=" << msg.angular.z);

 // Wait until it's time for another iteration.

    rate.sleep();
  }
}
