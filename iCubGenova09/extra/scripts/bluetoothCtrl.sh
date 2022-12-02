#!/bin/bash

# Before running, start rfcomm with the command
# sudo rfcomm -r listen /dev/rfcomm0 1
# Then, connect the app.
# Once connected, run
# sudo chmod a+rw /dev/rfcomm0
# and then start this script

REQUESTED_FAULT_TIMES=3
FAULT_TIMEOUT=5
ROBOT_NAME=icub

REQUESTED_FAULT_TIMES=$((REQUESTED_FAULT_TIMES-1)) #The counter starts from zero
DROP_NEXT_LINE=false
FAULT_TIMES=0
PART_SELECTED=none
MODE_SELECTED=none
LAST_FAULT=$SECONDS
JOINT_LIST=""
PING_COUNTER=0

function send_command
{
    for a in $JOINT_LIST; do
	echo "set icmd cmod $a $1"  | yarp rpc /$ROBOT_NAME/$PART_SELECTED/rpc:i
    done
}

function parse_part
{
    output_message="Received part: "

    case $1 in

    0)
    output_message="${output_message} None"
    PART_SELECTED=none
    JOINT_LIST=""
    ;;

    1)
    output_message="${output_message} Right Leg"
    PART_SELECTED=right_leg
    JOINT_LIST="0 1 2 3 4 5"
    ;;

    2)
    output_message="${output_message} Left Leg"
    PART_SELECTED=left_leg
    JOINT_LIST="0 1 2 3 4 5"
    ;;

    3)
    output_message="${output_message} Right Arm"
    PART_SELECTED=right_arm
    JOINT_LIST="0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15"
    ;;

    4)
    output_message="${output_message} Left Arm"
    PART_SELECTED=left_arm
    JOINT_LIST="0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15"
    ;;

    5)
    output_message="${output_message} Torso"
    PART_SELECTED=torso
    JOINT_LIST="0 1 2"
    ;;

    6)
    output_message="${output_message} Head"
    PART_SELECTED=head
    JOINT_LIST="0 1 2 3 4 5"
    ;;

    7)
    output_message="${output_message} Face"
    PART_SELECTED=face
    JOINT_LIST="0"
    ;;

    *)
    output_message="${output_message} Unknown part"
    PART_SELECTED=none
    JOINT_LIST=""
    ;;

    esac

}

function parse_mode
{
   output_message="Received mode: "

   case $1 in

   0)
   PING_COUNTER=$((PING_COUNTER+1))
   output_message="Ping (#${PING_COUNTER})"
   ;;

   1)
   output_message="${output_message} Idle"
   DROP_NEXT_LINE=true
   send_command idl
   ;;

   -1)
   output_message="${output_message} Run"
   DROP_NEXT_LINE=true
   send_command pos
   ;;

   *)
   output_message="${output_message} Unknown mode"
   ;;

   esac
}

function fault
{
    if [[ $(($SECONDS - LAST_FAULT)) > $FAULT_TIMEOUT ]]; then
        FAULT_TIMES=0
    fi

    if [[ $FAULT_TIMES < $REQUESTED_FAULT_TIMES ]]; then
    	output_message="FAULT Received. Press other $((REQUESTED_FAULT_TIMES-FAULT_TIMES)) time(s) to confirm!"
    	FAULT_TIMES=$((FAULT_TIMES+1))
    	LAST_FAULT=$SECONDS
    	return
    fi

    killall WalkingModule
    killall HapticGloveModule

    #Set all parts to position
    part_list="0 1 2 3 4 5 6 7"
    for p in $part_list; do
        parse_part $p
        send_command pos
    done

    output_message="FAULT! FAULT! FAULT!"
}

function parse_line
{

    if [[ $1 == "fault" ]]; then
        fault
        return
    fi

    if [[ $1 == "part" ]]; then
        parse_part $2
        return
    fi

    if [[ $1 == "mode" ]]; then
        parse_mode $2
        return
    fi

}

while read -r line ; do

        echo "Received (raw): ${line}"

        if [[ "$DROP_NEXT_LINE" = true ]]; then
            DROP_NEXT_LINE=false
    	    continue
        fi

        parse_line ${line}

        echo ${output_message}

        echo ${output_message} > /dev/rfcomm0

done < /dev/rfcomm0


