#!/usr/bin/bash
################################################################################
#                                                                              #
# Copyright (C) 2023 Fondazione Istitito Italiano di Tecnologia (IIT)          #
# All Rights Reserved.                                                         #
#                                                                              #
################################################################################

# search for paths
echo "Searching for required resources..."
file_yri=$(YARP_ROBOT_NAME=$1 yarp resource --context yarprobotinterface --from yarprobotinterface.ini | tail -1 | sed 's/\"//g')
dir_robot=$(dirname ${file_yri})
file_general=$(find ${dir_robot} -name "general.xml")
file_pc104=$(find ${dir_robot} -name "pc104.xml")

# skip if not enough info
if [[ ! -f "${file_yri}" || ! -f "${file_general}" || ! -f "${file_pc104}" ]]; then
  echo "$1 robot doesn't contain the info required for performing dry-run → skipped!"
  exit 0
fi

# prepare for dry-run
echo "Preparing the robot..."
xmlstarlet edit --inplace --update "/params/group/param[@name='skipCalibration']" --value 'true' ${file_general}
xmlstarlet edit --inplace --delete "/params/group[@name='DEBUG']" ${file_pc104}
xmlstarlet edit --inplace --subnode /params --type elem --name "group" --var new_node '$prev' \
                --insert '$new_node' --type attr --name "name" --value 'DEBUG' ${file_pc104}
xmlstarlet edit --inplace --subnode "/params/group[@name='DEBUG']" --type elem --name "param" --var new_node '$prev' \
                --insert '$new_node' --type attr --name "name" --value 'embBoardsConnected' ${file_pc104}
xmlstarlet edit --inplace --update "/params/group[@name='DEBUG']/param" --value '0' ${file_pc104}

# perform dry-run
echo "Starting yarpserver..."
yarpserver --write --silent &
yarp wait /root

echo "Starting yarprobotinterface..."
log_file=dry-run_log_$1.txt
YARP_ROBOT_NAME=$1 yarprobotinterface > ${log_file} 2>&1 &

# robot_port may not be opened → we cannot use `yarp wait`
robot_port=/$1/yarprobotinterface
echo "Checking the existence of ${robot_port}..."
for i in {1..5}
do
  if yarp exists ${robot_port}; then
    echo "${robot_port} is active"
    break
  fi
  sleep 1
done

echo "Checking shutdown condition..."
while true
do
  response=$(echo "get_phase" | yarp rpc ${robot_port})
  if [[ "${response}" == *"run"* ]]; then
    echo "yarprobotinterface was running happily"
    break
  fi

  if ! pgrep yarprobotinterface > /dev/null; then
    echo "yarprobotinterface didn't run correctly"
    break
  fi
  sleep 1
done

# clean up
echo "Cleaning up..."
killall yarpserver

# parse the log

exit 0
