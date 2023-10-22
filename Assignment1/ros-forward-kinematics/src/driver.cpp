// This program publishes random velocity commands

//Including the necessary ROS and C++ libraries
#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <stdlib.h>

//In main function,the ROS nodeis initialized with the name "publish_velocity" and a NodeHandle nh is created,it allows interaction with the ROS system.

int main(int argc, char **argv) {
  ros::init(argc, argv, "publish_velocity");
  ros::NodeHandle nh;

 // sets up a publisher named 'pub' for the"cmd_vel" topic.It will publish message of type 'geometry_msgs::Twist' with a queue size of 1.
  
  ros::Publisher pub = nh.advertise<geometry_msgs::Twist>(
      "cmd_vel", 1);   

 //  ensures that each run of the program generates  random values. 
  
  srand(time(0));

 // to control the loop's execution rate
  
  ros::Rate rate(2);
  while(ros::ok()) {
    
    // Create and send a random velocity command.
    //Inside the loop, random values for linear and angular velocities are generated.
    
    geometry_msgs::Twist msg;
    msg.linear.x = double(rand())/double(RAND_MAX);
    msg.angular.z = 2*double(rand())/double(RAND_MAX)-1;
    pub.publish(msg);
ROS_INFO_STREAM("Sending cmd_vel"
<< " LINEAR=" << msg.linear.x
<< " ANGULAR=" << msg.angular.z);

   //This line logs information about the sent velocity command 
    

    // Wait until it's time for another iteration.
    rate.sleep();
  }
}
