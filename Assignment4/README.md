### **ASSIGNMENT_4:  PRELIMINARY ROBOT SETUP**


**Github link**:https://github.com/prathibhasobha/ECG711-Assignments/blob/main/Assignment_4

**Youtube links:**

 **Led_blink**:  https://youtube.com/shorts/Lpelpt4QkIM

**Validating the working:**
Motor:https://youtube.com/shorts/CgHgy1fG7cI
IMU:https://youtube.com/shorts/0M10gKvK07o
Encoder:https://youtube.com/shorts/fHN3GxYBdQQ

**Calibrate the robot**:https://youtube.com/shorts/CgHgy1fG7cI

**Lidar and mapping:**
Echo scan:https://youtube.com/shorts/xQpI41YBHTM
Laser scan:https://youtube.com/shorts/cyn8fp6hWLs
Hector scan:https://youtu.be/Uyh9obMMYC0
 
### **LED blink for STM32**

STM32CubeIDE is an all-in-one multi-OS development tool, an advanced C/C++ development platform with peripheral configuration, code generation, code compilation and debugging functions for STM32 microcontrollers and microprocessors.

**Steps Followed**

•	Download STMCube IDE and STM programmer for Linux.

•	Open STMCube IDE ,then you need to select a workspace. Then save path according to the actual path.

•	Click File->New->STM32 Project.
			
•	Search and select the chip STM32F103RCT6, then click Next in the lower right corner to enter the next step

         ![image](https://github.com/prathibhasobha/ECG711-Assignments/assets/124483075/d23958f9-86ba-418d-b165-27bed0ab4096)

•	Enter the project name,  I named it as led_blink take LED and all otheparameters can be defaulted. Then, debug information, click 
            SYS->Debug under Pinout Configuration and select Serial Wire. Modify the system clock of STM32.The external crystal oscillator 
             is 8M frequency. 

•	Select RCC->HSE in Pinout Configuration and select Crystal/Ceramic Resonator. The HSE is the external clock, and the LSE is the 
            internal clock. Using the external clock can be more stable and efficient than the internal clock.

•	Switch to Clock Configuration to modify the frequency of HCLK to 72, and press Enter to confirm. 

•	Set the PC13 pin to GPIO_Output, and modify the Label to LED for convenience. 

•	Then press Ctrl+S to save, tick Remember my decision, and click Yes. This will automatically generate the code every time you 
             save.

•	Find the main function in the main.c file, and add the content to control the LED light under while(1). The function is that the LED 
            light flashes every 200 milliseconds. The code is as follows:

       ![image](https://github.com/prathibhasobha/ECG711-Assignments/assets/124483075/bf550141-ea19-43a7-9e08-439b8175e065)

•	Add the function of generating HEX files. Click Project->Properties->C/C++ Build->Settings->MCU Post build outputs in turn, 
            and then check the box before Convert to Intel Hex file(-O ihex). 

•	Click the hammer in the toolbar to start compiling the project. 

•	STM32CubeIDE will pop up the Console  and see 0 errors in compila-tion, and 0 warnings means the compilation is successful.

•	Next step is to burn the program, for that open the STM32cube  pro-grammer. In the open file upload the led_blink.hex file.

•	Connect the device, Insert one end of the USB data cable into the USB port of the computer, and the other end into the Micro 
            USB port of the Rosmaster expansion board. 

•	Hold boot and press Reset and set RTS=1.

•	Click connect on programmer software and click download.

   ![image](https://github.com/prathibhasobha/ECG711-Assignments/assets/124483075/3bb85975-2adf-4a9b-b1cf-6dd50aba7c3c)

**Result:**

     https://youtube.com/shorts/Lpelpt4QkIM
  
    ![image](https://github.com/prathibhasobha/ECG711-Assignments/assets/124483075/5537005a-1535-4ac3-8d38-41afe2358c6e)


**Robot Setup**

Attaching the images of the Robot that was made by setting up the motor, wheels, jetson nano lidar and ROS controller. The Jetson Nano sends serial port data to the expansion board via the USB port. The expansion board integrates a single chip microcomputer to receive and parse the serial port data, and then processes the specific commands to be executed.

![image](https://github.com/prathibhasobha/ECG711-Assignments/assets/124483075/8ee6d3e5-97c5-44a8-b54b-5befa070eb38)

![image](https://github.com/prathibhasobha/ECG711-Assignments/assets/124483075/143319e6-b757-4828-8558-228acc589cea)

![image](https://github.com/prathibhasobha/ECG711-Assignments/assets/124483075/946477ea-16e0-4445-af54-5e0ed606786f)

**### The working of the ROS-Controller for the motors, encoders, IMU**

**Motor:**	

The motor connecting line needs to be connected to the corresponding motor as shown in the figure below, otherwise it may cause the problem that the pro-gram does not match the phenomenon. Motor 1 corresponds to the motor in the upper left corner of the body, Motor 2 corresponds to the motor in the lower left corner, Motor 3 corresponds to the motor in the upper right corner, and Motor 4 corresponds to the motor in the lower right corner. 

![image](https://github.com/prathibhasobha/ECG711-Assignments/assets/124483075/ac2a6fa4-214e-42ba-a665-e8ff9d43c3a7)

Its working was checked by considering the rosmaster_v3.3.4.hex file and the controlling by considering keyboard.launch file.

![image](https://github.com/prathibhasobha/ECG711-Assignments/assets/124483075/e95dd8b8-349c-4156-bca9-f3130da20c90)

**Youtube link** :https://youtube.com/shorts/CgHgy1fG7cI

**IMU**

An IMU is a sensor device that typically combines multiple sensors to measure and report information about an object's acceleration, angular velocity, and sometimes magnetic field. In the context of robotics and ROS, IMUs are commonly used to provide information about a robot's orientation and motion. It is used for odometry and localization, sensor fusion motion planning, stabilization and control and mapping. The IMU working on the robot is as shown below.

![image](https://github.com/prathibhasobha/ECG711-Assignments/assets/124483075/26359180-60df-4d45-87fc-4ffbf15e24f3)

**YouTube Link** :https://youtube.com/shorts/0M10gKvK07o

**Encoder**

Encoders are essential components in robotics, providing information about the rotation and position of motors or wheels. Some key applications and uses of encoders in this robot are wheel odometry, closed loop control, speed control, mapping and localization, path planning. 

![image](https://github.com/prathibhasobha/ECG711-Assignments/assets/124483075/3035d988-4c21-4f00-bfc2-9067552a6f72)

**YouTube link** :https://youtube.com/shorts/fHN3GxYBdQQ

**Jenson nano with the SD-card image**

The Jetson Nano is designed for AI and deep learning applications. It's capable of running neural networks and is suitable for tasks such as image recognition, object detection, and classification. The Jetson Nano can be employed in autonomous vehicle projects, including drones and small-scale robotic vehicles. It can handle computer vision tasks essential for navigation and obstacle avoidance.
Downloaded the provided SD-card image and flashed it.


![image](https://github.com/prathibhasobha/ECG711-Assignments/assets/124483075/71130621-d173-411c-b6c6-b8b2c83d89db)

![image](https://github.com/prathibhasobha/ECG711-Assignments/assets/124483075/18260d2b-520b-4547-b54d-7c2cc8983fca)


**Calibrate the robot:**

The mobile dictionary mainly stores the relevant characters of the direction control and also the speed dictionary mainly stores the relevant characters of speed control.

![image](https://github.com/prathibhasobha/ECG711-Assignments/assets/124483075/d2a28856-8afd-43e6-8dec-4bbf92f4aecb)

![image](https://github.com/prathibhasobha/ECG711-Assignments/assets/124483075/954d1203-4379-40c8-b2d6-3542ecc49ab5)


Both the angular velocity and the linear velocity have a limit value, which cannot be increased all the time. When starting, the program will first obtain the speed limit value, and when increasing the speed, it will judge and process the increased value.

**YouTube link:**https://youtube.com/shorts/CgHgy1fG7cI

**Lidar and Mapping** 

It is necessary to declare the [RPLIDAR_TYPE] variable in advance in the [.bashrc] file according to different radar models. Open the [.bashrc] file. modify the radar model directly. After modification, refresh the environment variables.

**Echo Scan:**
![image](https://github.com/prathibhasobha/ECG711-Assignments/assets/124483075/68b416c3-924e-4b70-97e8-97c0a735c425)
**YouTube link:** https://youtube.com/shorts/xQpI41YBHTM

**Laser scan:**
![image](https://github.com/prathibhasobha/ECG711-Assignments/assets/124483075/ae04f18c-241a-42b6-9367-674140216f70)
**YouTube link:** https://youtube.com/shorts/cyn8fp6hWLs

**Hector scan:**
![image](https://github.com/prathibhasobha/ECG711-Assignments/assets/124483075/65dae710-70e3-46a5-9828-e8805846f88b)
**YouTube link** :https://youtu.be/Uyh9obMMYC0

































































































