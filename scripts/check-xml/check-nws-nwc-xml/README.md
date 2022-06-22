# check-nws-nwc-xml
This code has been used to check `xml` files consistency after manual modification due to the new `NWS/NWC` layers implemented in `YARP-3.5`.
The program uses `XSD` schema and `XPATH` to check `XML` files.

## Usage
1. Install the `libxml2-utils` package : 

```sh
sudo apt install libxml2-utils
```

2. Build the code :

```sh
cd <your-robots-configuration-folder>/experimentalSetups/check-nws-nwc-xml
mkdir build
cd build
ccmake ..
make
```

3. Run the program :

```sh
cd <your-robots-configuration-folder>/experimentalSetups/check-nws-nwc-xml/build
./check-nws-nwc-xml <robot-folder-absolute-path>
```
## Example

Run : 

```sh
./check-nws-nwc-xml /home/tumme/icub-tech-iit/robots-configuration/iCubLausanne01/
```

Output : 

```
1 - test yarprobotinterface.ini presence **************

yarprobotinterface.ini FOUND! PASS

2 - test included xml files presence **************

found :/home/tumme/icub-tech-iit/robots-configuration/iCubLausanne01//cartesian/left_arm_cartesian.xml
found :/home/tumme/icub-tech-iit/robots-configuration/iCubLausanne01//cartesian/right_arm_cartesian.xml
found :/home/tumme/icub-tech-iit/robots-configuration/iCubLausanne01//wrappers/motorControl/left_arm-mc_wrapper.xml
found :/home/tumme/icub-tech-iit/robots-configuration/iCubLausanne01//wrappers/motorControl/right_arm-mc_wrapper.xml
found :/home/tumme/icub-tech-iit/robots-configuration/iCubLausanne01//wrappers/motorControl/left_leg-mc_wrapper.xml
found :/home/tumme/icub-tech-iit/robots-configuration/iCubLausanne01//wrappers/motorControl/right_leg-mc_wrapper.xml
found :/home/tumme/icub-tech-iit/robots-configuration/iCubLausanne01//wrappers/motorControl/head-mc_wrapper.xml
found :/home/tumme/icub-tech-iit/robots-configuration/iCubLausanne01//wrappers/motorControl/torso-mc_wrapper.xml
found :/home/tumme/icub-tech-iit/robots-configuration/iCubLausanne01//wrappers/motorControl/left_arm-mc_remapper.xml
found :/home/tumme/icub-tech-iit/robots-configuration/iCubLausanne01//wrappers/motorControl/right_arm-mc_remapper.xml
found :/home/tumme/icub-tech-iit/robots-configuration/iCubLausanne01//wrappers/motorControl/head-mc_remapper.xml
found :/home/tumme/icub-tech-iit/robots-configuration/iCubLausanne01//wrappers/motorControl/torso-mc_remapper.xml
found :/home/tumme/icub-tech-iit/robots-configuration/iCubLausanne01//wrappers/motorControl/left_leg-mc_remapper.xml
found :/home/tumme/icub-tech-iit/robots-configuration/iCubLausanne01//wrappers/motorControl/right_leg-mc_remapper.xml
found :/home/tumme/icub-tech-iit/robots-configuration/iCubLausanne01//hardware/motorControl/icub_left_arm.xml
found :/home/tumme/icub-tech-iit/robots-configuration/iCubLausanne01//hardware/motorControl/icub_left_hand.xml
found :/home/tumme/icub-tech-iit/robots-configuration/iCubLausanne01//hardware/motorControl/icub_right_arm.xml
found :/home/tumme/icub-tech-iit/robots-configuration/iCubLausanne01//hardware/motorControl/icub_right_hand.xml
found :/home/tumme/icub-tech-iit/robots-configuration/iCubLausanne01//hardware/motorControl/icub_left_leg.xml
found :/home/tumme/icub-tech-iit/robots-configuration/iCubLausanne01//hardware/motorControl/icub_right_leg.xml
found :/home/tumme/icub-tech-iit/robots-configuration/iCubLausanne01//hardware/motorControl/icub_head.xml
found :/home/tumme/icub-tech-iit/robots-configuration/iCubLausanne01//hardware/motorControl/icub_torso.xml
found :/home/tumme/icub-tech-iit/robots-configuration/iCubLausanne01//wrappers/VFT/left_arm_VFT_wrapper.xml
found :/home/tumme/icub-tech-iit/robots-configuration/iCubLausanne01//wrappers/VFT/left_leg_VFT_wrapper.xml
found :/home/tumme/icub-tech-iit/robots-configuration/iCubLausanne01//wrappers/VFT/right_arm_VFT_wrapper.xml
found :/home/tumme/icub-tech-iit/robots-configuration/iCubLausanne01//wrappers/VFT/right_leg_VFT_wrapper.xml
found :/home/tumme/icub-tech-iit/robots-configuration/iCubLausanne01//wrappers/VFT/torso_VFT_wrapper.xml
found :/home/tumme/icub-tech-iit/robots-configuration/iCubLausanne01//hardware/VFT/left_arm_virtual_strain.xml
found :/home/tumme/icub-tech-iit/robots-configuration/iCubLausanne01//hardware/VFT/left_leg_virtual_strain.xml
found :/home/tumme/icub-tech-iit/robots-configuration/iCubLausanne01//hardware/VFT/right_arm_virtual_strain.xml
found :/home/tumme/icub-tech-iit/robots-configuration/iCubLausanne01//hardware/VFT/right_leg_virtual_strain.xml
found :/home/tumme/icub-tech-iit/robots-configuration/iCubLausanne01//hardware/VFT/torso_virtual_strain.xml
found :/home/tumme/icub-tech-iit/robots-configuration/iCubLausanne01//wrappers/FT/left_arm_FT_wrapper.xml
found :/home/tumme/icub-tech-iit/robots-configuration/iCubLausanne01//wrappers/FT/left_leg_FT_wrapper.xml
found :/home/tumme/icub-tech-iit/robots-configuration/iCubLausanne01//wrappers/FT/right_arm_FT_wrapper.xml
found :/home/tumme/icub-tech-iit/robots-configuration/iCubLausanne01//wrappers/FT/right_leg_FT_wrapper.xml
found :/home/tumme/icub-tech-iit/robots-configuration/iCubLausanne01//wrappers/MAIS/left_hand_mais_wrapper.xml
found :/home/tumme/icub-tech-iit/robots-configuration/iCubLausanne01//wrappers/MAIS/right_hand_mais_wrapper.xml
found :/home/tumme/icub-tech-iit/robots-configuration/iCubLausanne01//hardware/FT/left_arm_strain.xml
found :/home/tumme/icub-tech-iit/robots-configuration/iCubLausanne01//hardware/FT/left_leg_strain.xml
found :/home/tumme/icub-tech-iit/robots-configuration/iCubLausanne01//hardware/FT/right_arm_strain.xml
found :/home/tumme/icub-tech-iit/robots-configuration/iCubLausanne01//hardware/FT/right_leg_strain.xml
found :/home/tumme/icub-tech-iit/robots-configuration/iCubLausanne01//hardware/MAIS/left_hand_mais.xml
found :/home/tumme/icub-tech-iit/robots-configuration/iCubLausanne01//hardware/MAIS/right_hand_mais.xml
found :/home/tumme/icub-tech-iit/robots-configuration/iCubLausanne01//wrappers/skin/left_arm_skin_wrapper.xml
found :/home/tumme/icub-tech-iit/robots-configuration/iCubLausanne01//wrappers/skin/right_arm_skin_wrapper.xml
found :/home/tumme/icub-tech-iit/robots-configuration/iCubLausanne01//wrappers/skin/torso_skin_wrapper.xml
found :/home/tumme/icub-tech-iit/robots-configuration/iCubLausanne01//hardware/skin/left_arm.xml
found :/home/tumme/icub-tech-iit/robots-configuration/iCubLausanne01//hardware/skin/right_arm.xml
found :/home/tumme/icub-tech-iit/robots-configuration/iCubLausanne01//hardware/skin/torso.xml
found :/home/tumme/icub-tech-iit/robots-configuration/iCubLausanne01//wrappers/inertials/head-imuFilter_wrapper.xml
found :/home/tumme/icub-tech-iit/robots-configuration/iCubLausanne01//wrappers/inertials/head-imuFilter.xml
found :/home/tumme/icub-tech-iit/robots-configuration/iCubLausanne01//wrappers/inertials/head-inertials_wrapper.xml
found :/home/tumme/icub-tech-iit/robots-configuration/iCubLausanne01//wrappers/inertials/head-inertials_wrapper-deprecated.xml
found :/home/tumme/icub-tech-iit/robots-configuration/iCubLausanne01//hardware/inertials/head-inertial.xml
found :/home/tumme/icub-tech-iit/robots-configuration/iCubLausanne01//calibrators/head_calib.xml
found :/home/tumme/icub-tech-iit/robots-configuration/iCubLausanne01//calibrators/torso_calib.xml
found :/home/tumme/icub-tech-iit/robots-configuration/iCubLausanne01//calibrators/right_leg_calib.xml
found :/home/tumme/icub-tech-iit/robots-configuration/iCubLausanne01//calibrators/left_leg_calib.xml
found :/home/tumme/icub-tech-iit/robots-configuration/iCubLausanne01//calibrators/left_arm_calib.xml
found :/home/tumme/icub-tech-iit/robots-configuration/iCubLausanne01//calibrators/right_arm_calib.xml
found :/home/tumme/icub-tech-iit/robots-configuration/iCubLausanne01//calibrators/left_hand_calib.xml
found :/home/tumme/icub-tech-iit/robots-configuration/iCubLausanne01//calibrators/right_hand_calib.xml

***************************************
PASS ! found 63 of 63 file included.


3 - test calibrators/wrappers/remappers/cartesian xml files consistency **************

head - CALIBRATOR CHECK PASSED!
head - WRAPPER CHECK PASSED!
head - REMAPPER CHECK PASSED!
torso - CALIBRATOR CHECK PASSED!
torso - WRAPPER CHECK PASSED!
torso - REMAPPER CHECK PASSED!
right_leg - CALIBRATOR CHECK PASSED!
right_leg - WRAPPER CHECK PASSED!
right_leg - REMAPPER CHECK PASSED!
left_leg - CALIBRATOR CHECK PASSED!
left_leg - WRAPPER CHECK PASSED!
left_leg - REMAPPER CHECK PASSED!
left_arm - CALIBRATOR CHECK PASSED!
left_arm - WRAPPER CHECK PASSED!
left_arm - REMAPPER CHECK PASSED!
left_arm - CARTESIAN CHECK PASSED!
right_arm - CALIBRATOR CHECK PASSED!
right_arm - WRAPPER CHECK PASSED!
right_arm - REMAPPER CHECK PASSED!
right_arm - CARTESIAN CHECK PASSED!

4 - test calibrators consistency with XSD schema **************

/home/tumme/icub-tech-iit/robots-configuration/iCubLausanne01//calibrators/head_calib.xml
/home/tumme/icub-tech-iit/robots-configuration/iCubLausanne01//calibrators/head_calib.xml validates
/home/tumme/icub-tech-iit/robots-configuration/iCubLausanne01//calibrators/torso_calib.xml
/home/tumme/icub-tech-iit/robots-configuration/iCubLausanne01//calibrators/torso_calib.xml validates
/home/tumme/icub-tech-iit/robots-configuration/iCubLausanne01//calibrators/right_leg_calib.xml
/home/tumme/icub-tech-iit/robots-configuration/iCubLausanne01//calibrators/right_leg_calib.xml validates
/home/tumme/icub-tech-iit/robots-configuration/iCubLausanne01//calibrators/left_leg_calib.xml
/home/tumme/icub-tech-iit/robots-configuration/iCubLausanne01//calibrators/left_leg_calib.xml validates
/home/tumme/icub-tech-iit/robots-configuration/iCubLausanne01//calibrators/left_arm_calib.xml
/home/tumme/icub-tech-iit/robots-configuration/iCubLausanne01//calibrators/left_arm_calib.xml validates
/home/tumme/icub-tech-iit/robots-configuration/iCubLausanne01//calibrators/right_arm_calib.xml
/home/tumme/icub-tech-iit/robots-configuration/iCubLausanne01//calibrators/right_arm_calib.xml validates
/home/tumme/icub-tech-iit/robots-configuration/iCubLausanne01//calibrators/left_hand_calib.xml
/home/tumme/icub-tech-iit/robots-configuration/iCubLausanne01//calibrators/left_hand_calib.xml validates
/home/tumme/icub-tech-iit/robots-configuration/iCubLausanne01//calibrators/right_hand_calib.xml
/home/tumme/icub-tech-iit/robots-configuration/iCubLausanne01//calibrators/right_hand_calib.xml validates
Calibrators XSD check passed!

5 - test cartesian consistency with XSD schema **************

/home/tumme/icub-tech-iit/robots-configuration/iCubLausanne01//cartesian/left_arm_cartesian.xml
/home/tumme/icub-tech-iit/robots-configuration/iCubLausanne01//cartesian/left_arm_cartesian.xml validates
/home/tumme/icub-tech-iit/robots-configuration/iCubLausanne01//cartesian/right_arm_cartesian.xml
/home/tumme/icub-tech-iit/robots-configuration/iCubLausanne01//cartesian/right_arm_cartesian.xml validates
Cartesian XSD check passed!

6 - test wrappers consistency with XSD schema **************

/home/tumme/icub-tech-iit/robots-configuration/iCubLausanne01//wrappers/motorControl/left_arm-mc_wrapper.xml
/home/tumme/icub-tech-iit/robots-configuration/iCubLausanne01//wrappers/motorControl/left_arm-mc_wrapper.xml validates
/home/tumme/icub-tech-iit/robots-configuration/iCubLausanne01//wrappers/motorControl/right_arm-mc_wrapper.xml
/home/tumme/icub-tech-iit/robots-configuration/iCubLausanne01//wrappers/motorControl/right_arm-mc_wrapper.xml validates
/home/tumme/icub-tech-iit/robots-configuration/iCubLausanne01//wrappers/motorControl/left_leg-mc_wrapper.xml
/home/tumme/icub-tech-iit/robots-configuration/iCubLausanne01//wrappers/motorControl/left_leg-mc_wrapper.xml validates
/home/tumme/icub-tech-iit/robots-configuration/iCubLausanne01//wrappers/motorControl/right_leg-mc_wrapper.xml
/home/tumme/icub-tech-iit/robots-configuration/iCubLausanne01//wrappers/motorControl/right_leg-mc_wrapper.xml validates
/home/tumme/icub-tech-iit/robots-configuration/iCubLausanne01//wrappers/motorControl/head-mc_wrapper.xml
/home/tumme/icub-tech-iit/robots-configuration/iCubLausanne01//wrappers/motorControl/head-mc_wrapper.xml validates
/home/tumme/icub-tech-iit/robots-configuration/iCubLausanne01//wrappers/motorControl/torso-mc_wrapper.xml
/home/tumme/icub-tech-iit/robots-configuration/iCubLausanne01//wrappers/motorControl/torso-mc_wrapper.xml validates
Wrappers XSD check passed!

7 - test remappers consistency with XSD schema **************

/home/tumme/icub-tech-iit/robots-configuration/iCubLausanne01//wrappers/motorControl/left_arm-mc_remapper.xml
/home/tumme/icub-tech-iit/robots-configuration/iCubLausanne01//wrappers/motorControl/left_arm-mc_remapper.xml validates
/home/tumme/icub-tech-iit/robots-configuration/iCubLausanne01//wrappers/motorControl/right_arm-mc_remapper.xml
/home/tumme/icub-tech-iit/robots-configuration/iCubLausanne01//wrappers/motorControl/right_arm-mc_remapper.xml validates
/home/tumme/icub-tech-iit/robots-configuration/iCubLausanne01//wrappers/motorControl/head-mc_remapper.xml
/home/tumme/icub-tech-iit/robots-configuration/iCubLausanne01//wrappers/motorControl/head-mc_remapper.xml validates
/home/tumme/icub-tech-iit/robots-configuration/iCubLausanne01//wrappers/motorControl/torso-mc_remapper.xml
/home/tumme/icub-tech-iit/robots-configuration/iCubLausanne01//wrappers/motorControl/torso-mc_remapper.xml validates
/home/tumme/icub-tech-iit/robots-configuration/iCubLausanne01//wrappers/motorControl/left_leg-mc_remapper.xml
/home/tumme/icub-tech-iit/robots-configuration/iCubLausanne01//wrappers/motorControl/left_leg-mc_remapper.xml validates
/home/tumme/icub-tech-iit/robots-configuration/iCubLausanne01//wrappers/motorControl/right_leg-mc_remapper.xml
/home/tumme/icub-tech-iit/robots-configuration/iCubLausanne01//wrappers/motorControl/right_leg-mc_remapper.xml validates
Remappers XSD check passed!

***************************************************

ALL TESTS PASSED!!

```