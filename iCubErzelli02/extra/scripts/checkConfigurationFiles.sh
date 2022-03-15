#!/bin/bash

diff -r --exclude="CMakeLists.txt" $ROBOTOLOGY_SUPERBUILD_SOURCE_DIR/src/robots-configuration/$YARP_ROBOT_NAME $ROBOTOLOGY_SUPERBUILD_SOURCE_DIR/build/install/share/ICUBcontrib/robots/$YARP_ROBOT_NAME | grep -ve dcm_walking -ve extra > /tmp/diff_out 2>&1

GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m' # No Color

if [[ -s /tmp/diff_out ]]; then
    echo -e "${RED}There are differences.${NC}"
    cat /tmp/diff_out
else
    echo -e "${GREEN}The configuration files in the source and in the install folder coincide.${NC}"
fi
