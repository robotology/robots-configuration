# Additional Commands

This folder contains a set of script and aliases that ease the use of the robot. 
In order to use them, we assume that ``robots-configuration`` has been installed using the [``robotology-superbuild``](https://github.com/robotology/robotology-superbuild), and that the ``ROBOTOLOGY_SUPERBUILD_SOURCE_DIR`` and ``YARP_ROBOT_NAME`` environmental variables have been set.
Then, in the ``.bashrc_iCub`` file, append the following lines
```sh
additionalCommandsFile=${ROBOTOLOGY_SUPERBUILD_SOURCE_DIR}/src/robots-configuration/${YARP_ROBOT_NAME}/extra/scripts/additionalCommands.sh

if [ -f "$additionalCommandsFile" ]; then
    source $additionalCommandsFile
fi
```

After opening a new terminal, you can type ``helpRobot`` to get a list of useful commands.
