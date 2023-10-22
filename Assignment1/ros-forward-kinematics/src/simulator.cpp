#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "turtlesim/Pose.h"
#include <cmath>                                                                           //Necessary ROS and C++ libraries


const double PI = 3.14159265359;                                                           //define the constant value for PI
const double WHEEL_DIST = 5.0;                                                             //distance between wheels

ros::Publisher pos_pub;                                                                     //ROS publisher for publishing the pose

void myCallbackVelCmd(const geometry_msgs::Twist& cmd_vel) {
    static double x = 0.0;                                                                  //Initializing the x coordinate 
    static double y = 0.0;                                                                   //Initializing the y coordinate
    static double th = 0.0;                                                                  //Initialize the robot's orientation

    ros::Time ctime = ros::Time::now();                                                      //fetching the current time
    static ros::Time ptime = ctime;                                                          //Initializing the previous time

    double dt = (ctime - ptime).toSec();                                                      //Calculation of the elapsed time

    turtlesim::Pose mypose;                                                                    //Creating a Pose message for robot's position and orientation

    double speed_right = (cmd_vel.angular.z * WHEEL_DIST) / 2 + cmd_vel.linear.x;
    double speed_left = cmd_vel.linear.x * 2 - speed_right * 2;                                  //Calculating the speeds of the left and right wheels of robot

    if (speed_right == speed_left) {
        x += speed_right * dt * cos(th);                                                          //update x based on liner velocity
        y += speed_right * dt * sin(th);                                                          //update Y based on linear velocity
        th = th;                                                                                  //orientation remains the same
    } else {
        double R = WHEEL_DIST / 2.0 * ((speed_right + speed_left) / (speed_right - speed_left));    //when robot moves ,the angular velocity is non-zero
        double ICC_x = x - R * sin(th);
        double ICC_y = y + R * cos(th);
        double w = (speed_right - speed_left) / WHEEL_DIST;
        double dth = w * dt;

        x = cos(dth) * (x - ICC_x) - sin(dth) * (y - ICC_y) + ICC_x;                         //Update x, y, and orientation  for the robot's movement
        y = sin(dth) * (x - ICC_x) + cos(dth) * (y - ICC_y) + ICC_y;
        th += dth;
    }

    mypose.x = x;                                                                             //calculate the pose message
    mypose.y = y;
    mypose.theta = th;

    pos_pub.publish(mypose);                                                                 // Publish  pose to the "mypose" topic

    ptime = ctime;                                                                           //updating the time
    ROS_INFO("pos:x %f", mypose.x);
    ROS_INFO("pos:y %f", mypose.y);
    ROS_INFO("pos:theta %f", mypose.theta);
    
}

int main(int argc, char **argv) {
    ros::init(argc, argv, "DiffDrive_simulator");                                             //initializing the ROS node
    ros::NodeHandle n;
    pos_pub = n.advertise<turtlesim::Pose>("/mypose", 100);                                  //Create a publisher to publish the robot's pose
    ros::Subscriber velocity = n.subscribe("/cmd_vel", 10, myCallbackVelCmd);                //Create a subscriber that listens to "cmd_vel" topic

    ros::spin();

    return 0;
}

