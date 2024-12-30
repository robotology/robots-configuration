#!/usr/bin/bash
################################################################################
#                                                                              #
# Copyright (C) 2024 Fondazione Istitito Italiano di Tecnologia (IIT)          #
# All Rights Reserved.                                                         #
#                                                                              #
################################################################################

mkdir -p build && cd build
cmake -DCMAKE_PREFIX_PATH=${DEPENDENCIES_DIR}/install \
      -DCMAKE_INSTALL_PREFIX=${DEPENDENCIES_DIR}/install \
      -DBUILD_TESTING:BOOL=ON \
      -DINSTALL_ALL_ROBOTS:BOOL=ON ../../../