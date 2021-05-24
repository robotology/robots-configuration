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

# Test if the microphone is working
test-microphone() {
    arecord -vvv -f dat /dev/null
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
${GREEN}goToBuildSuperbuild${NC} Go to the corresponding build folder of the robotology superbuild."'

if [ "$PS1" ]; then
  echo -e "Type ${GREEN}helpRobot${NC} for a list of useful commands."
fi

