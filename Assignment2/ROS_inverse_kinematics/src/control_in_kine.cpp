#include "ros/ros.h"
#include "geometry_msgs/Pose.h"
#include "geometry_msgs/Twist.h"

ros::Publisher velocity_pub;
ros::Subscriber goal_pose_sub;
geometry_msgs::Pose current_pose;

                                                   // Define PID controller gains 
double kp_linear = 1.0;
double ki_linear = 0.1;
double kd_linear = 0.01;
double kp_angular = 1.0;
double ki_angular = 0.1;
double kd_angular = 0.01;
double prev_error_linear = 0;
double integral_linear = 0;
double prev_error_angular = 0;
double integral_angular = 0;

                                                      // Function to calculate linear error
double computeLinearError(const geometry_msgs::Pose::ConstPtr& goal_pose) {
                                                     // Calculate the error based on your desired criteria
                                                     // For example, you can calculate the difference between the current and goal linear positions.
    double desired_linear = 1.0;                      // Replace with your desired linear position
    double current_linear = current_pose.position.x;  // Adjust with your current pose
    return desired_linear - current_linear;
}

                                                       // Function to calculate angular error
double computeAngularError(const geometry_msgs::Pose::ConstPtr& goal_pose) {
                                                       // Calculate the error based on your desired criteria
                                                      
    double desired_angular = 0.0;                      // Replace with your desired angular position
    double current_angular = current_pose.orientation.z;  // Adjust with your current pose
    return desired_angular - current_angular;
}

                                                          // Function to compute linear control using PID
double computeLinearControl(double error_linear) {
    integral_linear += error_linear;
    double derivative_linear = error_linear - prev_error_linear;
    double control_linear = kp_linear * error_linear + ki_linear * integral_linear + kd_linear * derivative_linear;
    prev_error_linear = error_linear;
    return control_linear;
}

                                                            // Function to compute angular control using PID
double computeAngularControl(double error_angular) {
    integral_angular += error_angular;
    double derivative_angular = error_angular - prev_error_angular;
    double control_angular = kp_angular * error_angular + ki_angular * integral_angular + kd_angular * derivative_angular;
    prev_error_angular = error_angular;
    return control_angular;
}

void poseCallback(const geometry_msgs::Pose::ConstPtr& goal_pose) {
                                                             // Calculate control commands using PID controller
    double error_linear = computeLinearError(goal_pose);
    double control_linear = computeLinearControl(error_linear);

    double error_angular = computeAngularError(goal_pose);
    double control_angular = computeAngularControl(error_angular);

                                                           // Publish the control commands
    geometry_msgs::Twist vel_msg;
    vel_msg.linear.x = control_linear;
    vel_msg.angular.z = control_angular;
    velocity_pub.publish(vel_msg);
}

int main(int argc, char **argv) {
    ros::init(argc, argv, "controller_node");
    ros::NodeHandle n;
    velocity_pub = n.advertise<geometry_msgs::Twist>("cmd_vel", 1000);
    goal_pose_sub = n.subscribe<geometry_msgs::Pose>("goal_pose", 1000, poseCallback);

    ros::spin();

    return 0;
}

