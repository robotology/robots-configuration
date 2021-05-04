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

##
alias goToBuildSuperbuild='cd ../../build/src/${PWD##*/}'

## Alias for running a diff between the source and the install of the configuration files
alias configurationSourceInstallDiff='bash ${ADDITIONAL_COMMANDS_DIR}/checkConfigurationFiles.sh'

GREEN='\033[0;32m'
NC='\033[0m' # No Color
## Alias for displaying info messages about the other aliases
alias helpRobot='echo -e "Here some useful commands:
${GREEN}robotsConfigurationInstaller${NC} Takes care of installing the robot configuration files from any folder.
${GREEN}gotoRobotsConfigurationFolder${NC} Go to the source folder of the robot configuration files.
${GREEN}configurationSourceInstallDiff${NC} Performs a diff between the source and install configuration files. If there is no difference, it prints nothing.
${GREEN}goToBuildSuperbuild${NC} Go to the corresponding build folder of the robotology superbuild."'
echo -e "Type ${GREEN}helpRobot${NC} for a list of useful commands."

