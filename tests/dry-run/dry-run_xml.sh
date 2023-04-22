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

# handle missing files
if [[ ! -f "${file_yri}" ]]; then
  echo "Unable to locate \"${file_yri}\" → skipped!"
  exit 0
fi

if [[ ! -f "${file_launch}" ]]; then
  echo "Unable to locate \"${file_launch}\" → error!"
  exit 1
fi

# specify the log filename
log_file=dry-run_log_$1_xml.txt

# check xml schemas
echo "Checking the XML syntax..."
if ! check-xml --robot-dir ${dir_robot} > ${log_file} 2>&1; then
  echo "Found errors!"
  exit 1
fi

# perform dry-run
echo "Starting yarpserver..."
yarpserver --write --silent &
yarp wait /root

echo "Starting yarprobotinterface..."
YARP_ROBOT_NAME=$1 yarprobotinterface --dryrun >> ${log_file} 2>&1 &

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

cleanup
exit ${exit_code}
