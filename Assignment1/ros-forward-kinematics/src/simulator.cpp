#include "ros/ros.h"
#include "geometry_msgs/Twist.h"
#include "turtlesim/Pose.h"
#include <cmath>

const double PI = 3.14159265359;
const double WHEEL_DIST = 5.0;

ros::Publisher pos_pub;

void myCallbackVelCmd(const geometry_msgs::Twist& cmd_vel) {
    static double x = 0.0;
    static double y = 0.0;
    static double th = 0.0;

    ros::Time ctime = ros::Time::now();
    static ros::Time ptime = ctime;

    double dt = (ctime - ptime).toSec();

    turtlesim::Pose mypose;

    double speed_right = (cmd_vel.angular.z * WHEEL_DIST) / 2 + cmd_vel.linear.x;
    double speed_left = cmd_vel.linear.x * 2 - speed_right * 2;

    if (speed_right == speed_left) {
        x += speed_right * dt * cos(th);
        y += speed_right * dt * sin(th);
        th = th;
    } else {
        double R = WHEEL_DIST / 2.0 * ((speed_right + speed_left) / (speed_right - speed_left));
        double ICC_x = x - R * sin(th);
        double ICC_y = y + R * cos(th);
        double w = (speed_right - speed_left) / WHEEL_DIST;
        double dth = w * dt;

        x = cos(dth) * (x - ICC_x) - sin(dth) * (y - ICC_y) + ICC_x;
        y = sin(dth) * (x - ICC_x) + cos(dth) * (y - ICC_y) + ICC_y;
        th += dth;
    }

    mypose.x = x;
    mypose.y = y;
    mypose.theta = th;

    pos_pub.publish(mypose);

    ptime = ctime;
    ROS_INFO("pos:x %f", mypose.x);
    ROS_INFO("pos:y %f", mypose.y);
    ROS_INFO("pos:theta %f", mypose.theta);
    
}

int main(int argc, char **argv) {
    ros::init(argc, argv, "DiffDrive_simulator");
    ros::NodeHandle n;
    pos_pub = n.advertise<turtlesim::Pose>("/mypose", 100);
    ros::Subscriber velocity = n.subscribe("/cmd_vel", 10, myCallbackVelCmd);

    ros::spin();

    return 0;
}

