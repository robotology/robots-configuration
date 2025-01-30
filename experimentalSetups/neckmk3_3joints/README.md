3 Joints Neck Setup
===================

This is the setup the neck MK3 that will be mounted on `iCub` and `ergoCub`.          
It consists of three motors and can be actuated using `yarprobotinterface` and `yarpmotorgui`.   
One motor is controlled by an `amc` board and the others by two `amcbldc` boards.          
All the parameters to move the setup are in the configuration files.            

### Attention!!
These configuration files are still a work in progres. The parameters for the different PIDs are not tuned, with the exception for the `POSITION_PID_PARAMETERS` with the `PWM` output. These last parameters were tuned with part of the head mounted, so they are not definitive. To launch this configuration run: `yarprobotinterface --config neck_3_joints_PWM.xml`.


### Picture of the setup 

|  |
| :---: |
| ![](assets/head_front.png) |
| **Figure 1** Setup front view |
| ![](assets/head_side.png) |
| **Figure 2** Setup side view |
 
