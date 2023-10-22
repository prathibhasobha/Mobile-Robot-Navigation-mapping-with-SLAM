#include "ros/ros.h"
#include "turtlesim/Pose.h"
#include "geometry_msgs/Twist.h"

ros::Publisher cmd_vel_pub;

void poseCallback(const turtlesim::Pose::ConstPtr& pose_msg) {
                                                                 // control logic based on the received pose information
    double desired_x = 5.0;
    double desired_y = 5.0;
    double desired_theta = 0.0;

                                                                  // Calculate control commands
    double linear_speed = 0.0;                                    
    double angular_speed = 0.0;  
    
                                                                 // Publish control commands
    geometry_msgs::Twist cmd_vel;
    cmd_vel.linear.x = linear_speed;
    cmd_vel.angular.z = angular_speed;
    cmd_vel_pub.publish(cmd_vel);
}

int main(int argc, char **argv) {
    ros::init(argc, argv, "driver_node");
    ros::NodeHandle n;
    cmd_vel_pub = n.advertise<geometry_msgs::Twist>("/cmd_vel", 1000);
    ros::Subscriber pose_sub = n.subscribe("/mypose", 1000, poseCallback);

    ros::Rate loop_rate(1);                                        // Publish at 1 Hz

    while (ros::ok()) {
        ros::spinOnce();
        loop_rate.sleep();
    }

    return 0;
}

