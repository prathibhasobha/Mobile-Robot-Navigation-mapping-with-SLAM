### **Assignment 1 - ROS – Forward Kinematics of a DDMWR- PRATHIBHA SOBHA**



**Youtube:**https://youtu.be/kKKwfhIWW8U  



**Steps taken**:

•	 **Start by installing ROS**: Begin by installing the ROS software on my system.

•	 **Set up a ROS Workspace**: Create a catkin workspace to organize your ROS packages.

•	 **Create a ROS Package:** Generate a ROS package that will house your C++ program (my_driver.cpp and my_simulator.cpp). 
            This can be done using the 'catkin_create_pkg' command.

•	 **Develop Your C++ Program**: Copy your C++ program into the created package. Remember to place it in the 'src/' directory 
           of your package. Ensure that you include all ROS headers and libraries in your C++ program and link against 'roscpp'.

•	 **Modify CMakeLists.txt:** Open the 'CMakeLists.txt' file located in your packages directory and make changes based on the 
           codes  name and node creation names.

•	**Build the Package**: Build the package using “catkin_make” in your catkin workspace:

•	**Source the Workspace**: After building, make sure to source your workspace to access the newly built package and its 
           executables.

•	**Run the C++ ROS Node**: You can now run your C++ ROS node using ‘rosrun’. 
            Now my C++ ROS program is all set to run the code.

**Description of code:**

Here,I created two separate C++ files: one for the driver and another for the simulator.

**•	Driver (my_driver.cpp):**

The provided C++ code is a ROS (Robot Operating System) node that simulates a velocity publisher. It generates random linear and angular velocity commands for a robot and publishes them to the “cmd_vel” topic. This code is useful for testing and development, providing a way to simulate velocity commands for robot movement.

**Functionalities used:**

**1.Initialization:**
     The ROS node is initialized with the name “publish_velocity” .

**2. NodeHandle Creation:**
     A NodeHandle is created to interact with the ROS system.

**3.Publisher Initialization:**
    A publisher (‘pub’)is created to send messages of type’geometry
_msgs::Twist’  to the “cmd_vel”  topic.

**4. Random Number Generation:**
     The random number generator is seeded with the current time.

**5. Main Loop:**
    The main loop generates random linear and angular velocity commands, publishes them, logs the commands, and repeats at a rate of 2 Hz.

**6. Velocity Command Generation:**
     Random values are generated for linear and angular velocities.

**7. Publishing:**
    The generated velocity command is published to the “cmd_vel” topic. 

**8. Logging:**
     Information about the sent velocity command is logged to the console.

**9. Rate Control:**
     The loop waits to achieve the specified rate.

This code serves as a simulation for a velocity publisher node and can be adapted for testing robot motion in a ROS environment. 

**Result:**

![image](https://github.com/prathibhasobha/ECG711-Assignments/assets/124483075/b0cb7b0e-2661-40b0-8aae-b2374122d960)

**•	Simulator (my_simulator. cpp)**


This code is a simple differential drive simulator for a robot in a ROS environment. Here's a breakdown of the code:

**Libraries and Constants**

**ROS Headers**: The code includes necessary ROS and other headers.
Constants: It declares two constants,'PI' and 'WHEEL_DIST' , representing the mathematical constant Pi and the distance between the two wheels of the differential drive robot, respectively.

 **ROS Publisher**
The code declares a ROS publisher for the simulated pose of the robot.

**Callback Function:**
 There's a callback function 'myCallbackVelCmd'  that gets called whenever velocity commands ('geometry_msgs::Twist')  are received. This function computes the new pose of the robot based on the received velocity commands.

 **Pose Variables**
 It initializes static variables 'x', 'y' and 'th'representing the current position and orientation of the robot.

**Time Handling**
The code manages the current and previous time to calculate the time difference ('dt') between consecutive callbacks.

 **Differential Drive Kinematics**
 It calculates the speed of the left and right wheels and uses differential drive kinematics to update the robot's pose based on the received velocity commands.

 **Straight Line Motion and Circular Motion**
If the robot is moving straight, it updates the position based on linear velocity.
Circular Motion (Turning):  If the robot is turning, it calculates the center of rotation , angular velocity, and updates the position and orientation accordingly.

 **Pose Message and Publication**
 It creates a 'turtlesim::Pose' message with updated position and orientation.
Publish: The updated pose is published using the ROS publisher.

**ROS Initialization:**
 The `main` function initializes the ROS node and creates a publisher and a subscriber.

**ROS Spin**
It enters the ROS spin loop, allowing callbacks to be processed.

**Node Name and Topics**
The ROS node is named "DiffDrive_simulator"and it subscribes to the"/cmd_vel"  topic for velocity commands and publishes the simulated pose on the "/mypose" topic.

**Logging**
The code logs the current pose using 'ROS_INFO' statements.

**ROS Spin**
 The code enters the ROS spin loop, where it waits for callbacks to be called.

This code essentially simulates the movement of a differential drive robot in response to velocity commands and publishes its simulated pose. The differential drive kinematics are used to update the robot's pose based on the received linear and angular velocities.

**Result:**

![image](https://github.com/prathibhasobha/ECG711-Assignments/assets/124483075/938d880c-e8ac-4608-b053-7264d8cee27f)

**•	Launch (robot.launch)**

A ROS launch file is used to start one or more ROS nodes with specified parameters and configurations.
This code essentially simulates the movement of a differential drive robot in response to velocity commands and publishes its simulated pose. The differential drive kinematics are used to update the robot's pose based on the received linear and angular velocities.

**Result:**

![image](https://github.com/prathibhasobha/ECG711-Assignments/assets/124483075/68229188-8894-4eed-91cf-0aaafec22a70)
