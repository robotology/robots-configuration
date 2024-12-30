#!/usr/bin/bash
################################################################################
#                                                                              #
# Copyright (C) 2023 Fondazione Istitito Italiano di Tecnologia (IIT)          #
# All Rights Reserved.                                                         #
#                                                                              #
################################################################################

################################################################################
# helper routines

# clean up hanging resources
cleanup() {
  echo "Cleaning up..."
  killall -9 yarprobotinterface
  killall -9 yarpserver
}

# check if yarprobotinterface is running
# see https://askubuntu.com/a/988986
check_yri_runs() {
  if ps -o comm= -C "yarprobotinterface" 2>/dev/null | grep -x "yarprobotinterf" >/dev/null 2>&1; then
    return 0
  else
    echo "yarprobotinterface quit unexpectedly"
    return 1
  fi
}

################################################################################
# main

cleanup

# search for paths
echo "Searching for required resources..."
file_yri=$(YARP_ROBOT_NAME=$1 yarp resource --context yarprobotinterface --from yarprobotinterface.ini | tail -1 | sed 's/\"//g')
dir_robot=$(dirname ${file_yri})
file_launch=${dir_robot}/$(head -1 ${file_yri} | awk '{print $2}')
file_general=$(find ${dir_robot} -name "general.xml")
file_pc104=$(find ${dir_robot} -name "pc104.xml")

# handle missing files
if [[ ! -f "${file_yri}" ]]; then
  echo "Unable to locate \"${file_yri}\" → skipped!"
  exit 0
fi

if [[ ! -f "${file_launch}" ]]; then
  echo "Unable to locate \"${file_launch}\" → error!"
  exit 1
fi

if [[ ! -f "${file_general}" || ! -f "${file_pc104}" ]]; then
  echo "Missing info required for performing dry-run → skipped!"
  exit 0
fi

# skip CAN robots
if grep "cfw2" ${file_launch} > /dev/null; then
  echo "$1 is a CAN robot → skipped!"
  exit 0
fi

# prepare for dry-run
echo "Preparing the robot files..."

# make backups
cp ${file_launch}  ${file_launch}_bkp
cp ${file_general} ${file_general}_bkp
cp ${file_pc104}   ${file_pc104}_bkp

# disable inertial devices
xmlstarlet edit --inplace --delete "/robot/devices/xi:include[contains(@href,'inertials')]" ${file_launch}

# disable rpLidar devices
xmlstarlet edit --inplace --delete "/robot/devices/xi:include[contains(@href,'rpLidar')]" ${file_launch}

# disable wholebodydynamics
xmlstarlet edit --inplace --delete "/robot/devices/xi:include[contains(@href,'wholebodydynamics')]" ${file_launch}

# disable ros wrappers
xmlstarlet edit --inplace --delete "/robot/devices/xi:include[contains(@href,'_ros')]" ${file_launch}
xmlstarlet edit --inplace --delete "/robot/devices/xi:include[contains(@href,'_ros2')]" ${file_launch}

# disable calibration
xmlstarlet edit --inplace --update "/params/group/param[@name='skipCalibration']" --value 'true' ${file_general}

# enable the embObj dry-dun
xmlstarlet edit --inplace --delete "/params/group[@name='DEBUG']" ${file_pc104}
xmlstarlet edit --inplace --subnode /params --type elem --name "group" --var new_node '$prev' \
                --insert '$new_node' --type attr --name "name" --value 'DEBUG' ${file_pc104}
xmlstarlet edit --inplace --subnode "/params/group[@name='DEBUG']" --type elem --name "param" --var new_node '$prev' \
                --insert '$new_node' --type attr --name "name" --value 'embBoardsConnected' ${file_pc104}
xmlstarlet edit --inplace --update "/params/group[@name='DEBUG']/param" --value '0' ${file_pc104}

# specify the log filename
log_file=dry-run_log_$1_dev.txt

# perform dry-run
echo "Starting yarpserver..."
yarpserver --write --silent &
yarp wait /root

echo "Starting yarprobotinterface..."
YARP_ROBOT_NAME=$1 yarprobotinterface > ${log_file} 2>&1 &

exit_code=0

# robot_port may not be opened → we cannot use `yarp wait`
echo "Checking the robot port..."
while true
do
  robot_port=$(yarp name list | grep yarprobotinterface | awk '{print $3}')
  if [[ ! -z "${robot_port}" ]]; then
    echo "${robot_port} is active"
    break
  fi

  if ! check_yri_runs; then
    exit_code=1
    break
  fi
  
  sleep 1
done

while [[ ${exit_code} -eq 0 ]]
do
  response=$(echo "get_phase" | yarp rpc ${robot_port})
  if [[ "${response}" == *"run"* ]]; then
    echo "yarprobotinterface was running happily"
    break
  fi

  if ! check_yri_runs; then
    exit_code=1
  fi

  sleep 1
done

# restore backups
mv ${file_launch}_bkp  ${file_launch}
mv ${file_general}_bkp ${file_general}
mv ${file_pc104}_bkp   ${file_pc104}

cleanup
exit ${exit_code}
