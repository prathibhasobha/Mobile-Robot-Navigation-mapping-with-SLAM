//Necessary headers

#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "turtlesim/Pose.h"
#include <cmath>

//declairing constants 

const double PI = 3.14159265359;
const double WHEEL_DIST = 5.0;

//publisher for the pose

ros::Publisher pos_pub;

Callback functionnfor velocity commands

void myCallbackVelCmd(const geometry_msgs::Twist& cmd_vel) {

//Initialize pose variables

    static double x = 0.0;
    static double y = 0.0;
    static double th = 0.0;

//Get current time

    ros::Time ctime = ros::Time::now();
    static ros::Time ptime = ctime;

//calculate time difference

    double dt = (ctime - ptime).toSec();

//calculate turtlesim pose message
   
 turtlesim::Pose mypose;

//calcualte speeds of the left and right wheels

    double speed_right = (cmd_vel.angular.z * WHEEL_DIST) / 2 + cmd_vel.linear.x;
    double speed_left = cmd_vel.linear.x * 2 - speed_right * 2;

//diffrential drive kinematics    

if (speed_right == speed_left) {

//staight line motion

        x += speed_right * dt * cos(th);
        y += speed_right * dt * sin(th);
        th = th;  // No change in orientation
    } else {

//circular motion (turning)

        double R = WHEEL_DIST / 2.0 * ((speed_right + speed_left) / (speed_right - speed_left));
        double ICC_x = x - R * sin(th);
        double ICC_y = y + R * cos(th);
        double w = (speed_right - speed_left) / WHEEL_DIST;
        double dth = w * dt;

//update the pose based on the center of rotation.

        x = cos(dth) * (x - ICC_x) - sin(dth) * (y - ICC_y) + ICC_x;
        y = sin(dth) * (x - ICC_x) + cos(dth) * (y - ICC_y) + ICC_y;
        th += dth;                   //update the orientation
    }

//the pose messages

    mypose.x = x;
    mypose.y = y;
    mypose.theta = th;

//publish the updated pose

    pos_pub.publish(mypose);

//update the previous time

    ptime = ctime;

//log the current pose

    ROS_INFO("pos:x %f", mypose.x);
    ROS_INFO("pos:y %f", mypose.y);
    ROS_INFO("pos:theta %f", mypose.theta);
    
}

int main(int argc, char **argv) {

//Initialize the ROS node

    ros::init(argc, argv, "DiffDrive_simulator");
    ros::NodeHandle n;

//create a publisher for the simulated pose

    pos_pub = n.advertise<turtlesim::Pose>("/mypose", 100);

//create a subscriber for velocity

    ros::Subscriber velocity = n.subscribe("/cmd_vel", 10, myCallbackVelCmd);

//ROS spin loop

    ros::spin();

    return 0;
}

