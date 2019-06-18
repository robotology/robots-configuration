#/bin/bash
# testSkin.sh
# sets the robot name in all files
# by tumme

 if [ "$1" == "" ]; then
    echo "missing robot name argument!"
    echo ""
    echo "e.g. ./setRobotName.sh iCubGenova01 -> sets robot name to iCubGenova01 in all files"
    echo ""
 else
   if test -f "icub_all.xml"; then 
     find . -type f -print0 | xargs -0 sed -i "s/robot=\".*\" /robot=\"$1\" /g; s/<robot.*name=\".*\" /<robot name=\"$1\" /g;" 
   else
     echo "this is not a robot directory!"
   fi
 fi      
