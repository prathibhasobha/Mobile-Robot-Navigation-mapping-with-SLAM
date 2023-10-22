#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/Pose2D.h>

void PoseCallback(const geometry_msg::Pose2D& pose){
            gpose = pose;
        }

int main(int argc, char **argv){
ros::init(argc, argv, "PID_Control");
ros::NodeHandle nh;

ros::Subscriber pose = nh.subscribe<geometry_msgs::Pose2D>("goal_pose",1000,PoseCallback);
ros::Publisher velocity_publisher = nh.advertise<geometry_msgs::Twist>("cmd_vel", 1000);
...
}

float getDistance()
{
 return sqrt(pow((current_pose.x - gpose.x), 2) + pow((current_pose.y - gpose.y), 2));
}

float getAngle()
{
 return ((atan2(gpose.y - current_pose.y, gpose.x - current_pose.x)) - current_pose.theta);
}

void moveGoal(geometry_msgs::Pose2D goal_pose, double distance_tolerance)
{
//We implement a PID Controller. We need to go from (x,y) to (x',y').
//Then, linear velocity v' = K ((x'-x)^2 + (y'-y)^2)^0.5 where K is the constant and ((x'-x)^2 + (y'-y)^2)^0.5 is the Euclidian distance.
//The steering angle theta = tan^-1(y'-y)/(x'-x) is the angle between these 2 points.
    geometry_msgs::Twist vel_msg;
    float e_theta = 0;
    float integral_theta = 0;
    float diff_theta = 0;
    float e_dist = 0;
    float integral_dist = 0;
    float diff_dist = 0;
    ros::Rate loop_rate(10);
    e_theta = getAngle();
    e_dist = getDistance();
    float k1 = 7.5, k2 = 0.00001, k3 = 0.01;
    do {
         //linear velocity
        vel_msg.linear.x = k1 *e_dist / 20.0) + (k2 *integral_dist) + (k3 *diff_dist);
        vel_msg.linear.y = 0;
        vel_msg.linear.z = 0;
        //angular velocity
        vel_msg.angular.x = 0;
        vel_msg.angular.y = 0;
        vel_msg.angular.z = (k1 *e_theta) + (k2 *integral_theta) + (k3 *diff_theta);
        e_theta = getAngle();
        e_dist = getDistance();

        integral_theta += e_theta;
        integral_dist += e_dist;

        diff_dist = e_dist - diff_dist;
        diff_theta = e_theta - diff_theta;

        velocity_publisher.publish(vel_msg);
        ros::spinOnce();
        loop_rate.sleep();
    } while (e_dist > distance_tolerance);
    cout << "end move goal" << endl;
    vel_msg.linear.x = 0;
    vel_msg.angular.z = 0;
    velocity_publisher.publish(vel_msg);

}
