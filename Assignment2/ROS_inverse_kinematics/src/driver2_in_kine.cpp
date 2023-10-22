#include <stdlib.h>                  //  the standard C library.
#include <ros/ros.h>                 //  the ROS library
#include "geometry_msgs/Pose2D.h"   //  the Pose2D message type.



int main(int argc, char **argv) {
    ros::init(argc, argv, "driver");  // Initialize the ROS node with the name "driver".
    ros::NodeHandle nh;               // Create a NodeHandle for this node.


// Initialize a ROS publisher that publishes Pose2D messages

    ros::Publisher driver_pub = nh.advertise<geometry_msgs::Pose2D>("goal_pose", 1); 

    geometry_msgs::Pose2D goal_pose;   // Create a Pose2D message object.
    
    ros::Rate naptime(2);              // Create a loop frequency (2 Hz)
    
    while (ros::ok())                  // Enter the main loop 
    {
        geometry_msgs::Pose2D goal_pose;  //Create a new Pose2D message 
        goal_pose.x = 5.0; 
        goal_pose.y = 3.5;
        goal_pose.theta = 0.8 ;
        
        //current Pose2D values 
        
        ROS_INFO("Pose: x = %f, y = %f, theta = %f rad", goal_pose.x, goal_pose.y, goal_pose.theta);  
        
        // Publish the Pose2D message on the "goal_pose" topic
        
        driver_pub.publish(goal_pose);  
        naptime.sleep();  
    }
}
