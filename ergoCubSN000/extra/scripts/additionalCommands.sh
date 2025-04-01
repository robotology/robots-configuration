## Additional aliases and commands to use the robot

getParentDir () {
    SOURCE="${1}"
    while [ -h "$SOURCE" ]; do # resolve $SOURCE until the file is no longer a symlink
      DIR="$( cd -P "$( dirname "$SOURCE" )" >/dev/null 2>&1 && pwd )"
      SOURCE="$(readlink "$SOURCE")"
      [[ $SOURCE != /* ]] && SOURCE="$DIR/$SOURCE" # if $SOURCE was a relative symlink, we need to resolve it relative to the path where the symlink file was located
    done
    DIR="$( cd -P "$( dirname "$SOURCE" )" >/dev/null 2>&1 && pwd )"
}

getParentDir "${BASH_SOURCE[0]}"

# The directory where this script is
export ADDITIONAL_COMMANDS_DIR="$DIR"


#Robots Configuration settings
alias robotsConfigurationInstaller='bash ${ADDITIONAL_COMMANDS_DIR}/installRobotsConfiguration.sh'
export ROBOTS_CONFIGURATION_DIR=${ROBOTOLOGY_SUPERBUILD_SOURCE_DIR}/src/robots-configuration/${YARP_ROBOT_NAME}
alias gotoRobotsConfigurationFolder='cd $ROBOTS_CONFIGURATION_DIR'

#Automatic Joypad configuration
alias connectToJoypad='sudo expect ${ADDITIONAL_COMMANDS_DIR}/bluetoothConnect.sh 28:9A:4B:08:E1:1B'

# Go to DCM folder
alias dcmFolder='cd ${ROBOTOLOGY_SUPERBUILD_SOURCE_DIR}/src/walking-controllers/src/WalkingModule/app/robots/${YARP_ROBOT_NAME}'

# Go to the corresponding build folder in the superbuild
alias goToBuildSuperbuild='cd ../../build/src/${PWD##*/}'

## Alias for running a diff between the source and the install of the configuration files
alias configurationSourceInstallDiff='bash ${ADDITIONAL_COMMANDS_DIR}/checkConfigurationFiles.sh'

alias test-speaker='speaker-test -t wav -c 1'

# Alias for running whole-body-dynamics
alias runYarpRobotInterface='YARP_FORWARD_LOG_ENABLE=1 yarprobotinterface'
alias runYarpRobotInterfaceTwoRobots='YARP_PORT_PREFIX=/ergocub000 YARP_FORWARD_LOG_ENABLE=1 yarprobotinterface'

# Test if the microphone is working
test-microphone() {
    arecord -vvv -f dat /dev/null
}

alias trigger-click='DISPLAY=:0 xdotool click 1'

alias list-windows='DISPLAY=:0 wmctrl -lp'

alias close-window='DISPLAY=:0 wmctrl -c'

_WIFI_INTERFACE=`iw dev | awk '$1=="Interface"{print $2}'`
alias disable-wifi-powersave="sudo iw dev ${_WIFI_INTERFACE} set power_save off"
unset _WIFI_INTERFACE

function set-blf-webcam() {
    # Check if the camera number is provided
    if [ "$#" -ne 1 ]; then
        echo "Usage: set-blf-webcam <camera_number>"
        return 1
    fi

    CAMERA_NUMBER="$1"

    # Construct the path to the XML file
    XML_FILE="${ROBOTOLOGY_SUPERBUILD_SOURCE_DIR}/src/bipedal-locomotion-framework/devices/YarpRobotLog\
gerDevice/app/robots/${YARP_ROBOT_NAME}/blf-yarp-robot-logger-interfaces/webcams.xml"

    # Check if the XML file exists
    if [ ! -f "$XML_FILE" ]; then
        echo "Error: File $XML_FILE does not exist."
        return 1
    fi

    # Modify the camera number in the XML file
    sed -i 's|\(<param name="camera">\)[^<]*\(</param>\)|\1'"$CAMERA_NUMBER"'\2|' "$XML_FILE"

    echo "Camera number in $XML_FILE has been set to $CAMERA_NUMBER."

    cd ${ROBOTOLOGY_SUPERBUILD_SOURCE_DIR}/build/src/bipedal-locomotion-framework
    cmake . && cmake --build . --target install
    cd -
}


GREEN='\033[0;32m'
NC='\033[0m' # No Color
## Alias for displaying info messages about the other aliases
alias helpRobot='echo -e "Here some useful commands:
${GREEN}robotsConfigurationInstaller${NC} Takes care of installing the robot configuration files from any folder.
${GREEN}gotoRobotsConfigurationFolder${NC} Go to the source folder of the robot configuration files.
${GREEN}configurationSourceInstallDiff${NC} Performs a diff between the source and install configuration files. If there is no difference, it prints nothing.
${GREEN}connectToJoypad${NC} To reconnect the bluetooth connection of the robot joypad.
${GREEN}test-speaker${NC} Test if the speaker is working.
${GREEN}test-microphone${NC} Test if the micorphone is working.
${GREEN}dcmFolder${NC} Go to the robot walking configuration files.
${GREEN}goToBuildSuperbuild${NC} Go to the corresponding build folder of the robotology superbuild.
${GREEN}trigger-click${NC} Emulates a mouse click to make banners disappear on the ergoCub screen.
${GREEN}list-windows${NC} List the open windows. The first output is the window ID. The third value is the ID of the process owning the window.
${GREEN}close-window${NC} Close a window given the Window ID.
${GREEN}disable-wifi-powersave${NC} Disable the WiFi powersave.
${GREEN}set-blf-webcam${NC} Bash script that can be used to set the number of the blf webcam in the logger. IT WILL RECOMPILE AND INSTALL BLF.
${GREEN}runYarpRobotInterface${NC} Run yarprobotinterface with whole-body-dynamics."'

if [ "$PS1" ]; then
  echo -e "Type ${GREEN}helpRobot${NC} for a list of useful commands."

  # automatic terminator title
  trap 'echo -ne "\033]2;$(history 1 | sed "s/^[ ]*[0-9]*[ ]*//g")\007"' DEBUG
fi

