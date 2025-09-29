#!/bin/bash

if [[ -v "${ICUB_BUILD_PATHNAME}" ]]; then
    BUILD_DIR=${ICUB_BUILD_PATHNAME}
else
    BUILD_DIR='build';
fi

echo "Running make install in ${ROBOTOLOGY_SUPERBUILD_SOURCE_DIR}/${BUILD_DIR}/src/robots-configuration"

cd ${ROBOTOLOGY_SUPERBUILD_SOURCE_DIR}/${BUILD_DIR}/src/robots-configuration
cmake . && make install
