FROM ubuntu:latest
LABEL org.opencontainers.image.title="Robots Configuration Dry-Run"
LABEL org.opencontainers.image.description="Infrastructure for perfoming dry-run of robot configuration files"
LABEL org.opencontainers.image.source="https://github.com/robotology/robots-configuration"
LABEL org.opencontainers.image.authors="Ugo Pattacini <ugo.pattacini@iit.it>"

# Non-interactive installation mode
ENV DEBIAN_FRONTEND=noninteractive

# Install essentials
RUN apt update && \
    apt install -y sudo apt-utils apt-transport-https software-properties-common build-essential psmisc procps gdb gdebi autoconf locales \
                  git gitk cmake libace-dev libtinyxml-dev libtinyxml2-dev libxml2-dev libxml2-utils \
                  coinor-libipopt-dev libeigen3-dev libgsl-dev libopencv-dev libsdl1.2-dev \
                  libi2c-dev i2c-tools xmlstarlet magic-wormhole

# Select options
ARG DEPENDENCIES_DIR

# Do preparations
RUN locale-gen en_US.UTF-8 && \
    mkdir -p ${DEPENDENCIES_DIR}

# Install dependencies
RUN cd ${DEPENDENCIES_DIR} && \
    git clone https://github.com/robotology/icub-main.git && \
    git clone https://github.com/robotology/icub-firmware-shared.git && \
    cd icub-main && git checkout devel && \
    grep -m 1 YCM_REQUIRED_VERSION CMakeLists.txt | sed "s/[^0-9.]//g" > ${DEPENDENCIES_DIR}/YCM_VERSION.txt && \
    grep -m 1 YARP_REQUIRED_VERSION CMakeLists.txt | sed "s/[^0-9.]//g" > ${DEPENDENCIES_DIR}/YARP_VERSION.txt && \
    cat ${DEPENDENCIES_DIR}/YARP_VERSION.txt | awk -F '.' '{ print $1 }' > ${DEPENDENCIES_DIR}/YARP_VERSION_MAJOR.txt && \
    cat ${DEPENDENCIES_DIR}/YARP_VERSION.txt | awk -F '.' '{ print $2 }' > ${DEPENDENCIES_DIR}/YARP_VERSION_MINOR.txt && \
    grep -m 1 icub_firmware_shared_VERSION conf/iCubFindDependencies.cmake | sed "s/[^0-9.]//g" > ${DEPENDENCIES_DIR}/icub_firmware_shared_VERSION.txt && \
    cd ${DEPENDENCIES_DIR}/icub-firmware-shared && \
    git tag > ${DEPENDENCIES_DIR}/icub_firmware_shared_RELEASES.txt && \
    if grep -q $(cat ${DEPENDENCIES_DIR}/icub_firmware_shared_VERSION.txt) ${DEPENDENCIES_DIR}/icub_firmware_shared_RELEASES.txt; then \
      git checkout v$(cat ${DEPENDENCIES_DIR}/icub_firmware_shared_VERSION.txt); \
    else \
      git checkout devel; \
    fi

# ycm
RUN cd ${DEPENDENCIES_DIR} && \
    git clone https://github.com/robotology/ycm.git && \
    cd ycm && mkdir -p build && cd build && \
    git checkout v$(cat ${DEPENDENCIES_DIR}/YCM_VERSION.txt) && \
    cmake .. -DCMAKE_INSTALL_PREFIX=${DEPENDENCIES_DIR}/install && \
    cmake --build . --config Release --target install

# yarp
RUN cd ${DEPENDENCIES_DIR} && \
    git clone https://github.com/robotology/yarp.git && \
    cd yarp && mkdir -p build && cd build && \
    git checkout yarp-$(cat ${DEPENDENCIES_DIR}/YARP_VERSION_MAJOR.txt).$(cat ${DEPENDENCIES_DIR}/YARP_VERSION_MINOR.txt) && \
    cmake .. \
          -DCMAKE_PREFIX_PATH=${DEPENDENCIES_DIR}/install \
          -DCMAKE_INSTALL_PREFIX=${DEPENDENCIES_DIR}/install \
          -DYARP_COMPILE_DEVICE_PLUGINS:BOOL=ON \
          -DYARP_COMPILE_CARRIER_PLUGINS:BOOL=ON \
          -DYARP_COMPILE_PORTMONITOR_PLUGINS:BOOL=ON \
          -DYARP_COMPILE_EXECUTABLES:BOOL=ON && \
    cmake --build . --config Release --target install

# yarp-device-xsensmt
RUN cd ${DEPENDENCIES_DIR} && \
    git clone https://github.com/robotology/yarp-device-xsensmt.git && \
    cd yarp-device-xsensmt && mkdir -p build && cd build && \
    git checkout $(git tag | tail -1) && \
    cmake .. \
          -DCMAKE_PREFIX_PATH=${DEPENDENCIES_DIR}/install \
          -DCMAKE_INSTALL_PREFIX=${DEPENDENCIES_DIR}/install && \
    cmake --build . --config Release --target install

# yarp-device-rplidar
#RUN cd ${DEPENDENCIES_DIR} && \
#    git clone https://github.com/robotology/yarp-device-rplidar.git && \
#    cd yarp-device-rplidar && mkdir -p build && cd build && \
#    git checkout master && \
#    cmake .. \
#          -DCMAKE_PREFIX_PATH=${DEPENDENCIES_DIR}/install \
#          -DCMAKE_INSTALL_PREFIX=${DEPENDENCIES_DIR}/install && \
#    cmake --build . --config Release --target install

# icub-firmware-shared
RUN cd ${DEPENDENCIES_DIR} && \
    cd icub-firmware-shared && mkdir -p build && cd build && \
    cmake .. \
          -DCMAKE_PREFIX_PATH=${DEPENDENCIES_DIR}/install \
          -DCMAKE_INSTALL_PREFIX=${DEPENDENCIES_DIR}/install && \
    cmake --build . --config Release --target install

# icub-main
RUN cd ${DEPENDENCIES_DIR} && \
    cd icub-main && mkdir -p build && cd build && \
    cmake .. \
          -DCMAKE_PREFIX_PATH=${DEPENDENCIES_DIR}/install \
          -DCMAKE_INSTALL_PREFIX=${DEPENDENCIES_DIR}/install \
          -DBUILD_SHARED_LIBS:BOOL=OFF \
          -DICUB_USE_icub_firmware_shared:BOOL=ON \
          -DENABLE_icubmod_embObjFTsensor:BOOL=ON \
          -DENABLE_icubmod_embObjIMU:BOOL=ON \
          -DENABLE_icubmod_embObjInertials:BOOL=ON \
          -DENABLE_icubmod_embObjMais:BOOL=ON \
          -DENABLE_icubmod_embObjMotionControl:BOOL=ON \
          -DENABLE_icubmod_embObjBattery:BOOL=ON \
          -DENABLE_icubmod_embObjSkin:BOOL=ON \
          -DENABLE_icubmod_embObjMultipleFTsensors:BOOL=ON \
          -DENABLE_icubmod_embObjPOS:BOOL=ON \
          -DENABLE_icubmod_embObjPSC:BOOL=ON \
          -DENABLE_icubmod_embObjBattery:BOOL=ON \
          -DENABLE_icubmod_canBusFtSensor:BOOL=ON \
          -DENABLE_icubmod_xsensmtx:BOOL=ON \
          -DENABLE_icubmod_skinWrapper:BOOL=ON \
          -DENABLE_icubmod_parametricCalibratorEth:BOOL=ON \
          -DENABLE_icubmod_cartesiancontrollerserver:BOOL=ON && \
    cmake --build . --config Release --target install

# navigation
RUN cd ${DEPENDENCIES_DIR} && \
    git clone https://github.com/robotology/navigation.git && \
    cd navigation && mkdir -p build && cd build && \
    git checkout master && \
    cmake .. \
          -DCMAKE_PREFIX_PATH=${DEPENDENCIES_DIR}/install \
          -DCMAKE_INSTALL_PREFIX=${DEPENDENCIES_DIR}/install && \
    cmake --build . --config Release --target install

# cer
RUN cd ${DEPENDENCIES_DIR} && \
    git clone https://github.com/robotology/cer.git && \
    cd cer && mkdir -p build && cd build && \
    git checkout devel && \
    cmake .. \
          -DCMAKE_PREFIX_PATH=${DEPENDENCIES_DIR}/install \
          -DCMAKE_INSTALL_PREFIX=${DEPENDENCIES_DIR}/install \
          -DENABLE_cermod_tripodMotionControl:BOOL=ON \
          -DENABLE_cermod_cerDoubleLidar:BOOL=ON && \
    cmake --build . --config Release --target install

# icub-contrib-common
RUN cd ${DEPENDENCIES_DIR} && \
    git clone https://github.com/robotology/icub-contrib-common.git && \
    cd icub-contrib-common && mkdir -p build && cd build && \
    git checkout master && \
    cmake .. \
          -DCMAKE_PREFIX_PATH=${DEPENDENCIES_DIR}/install \
          -DCMAKE_INSTALL_PREFIX=${DEPENDENCIES_DIR}/install && \
    cmake --build . --target install 

# Create user gitpod
RUN useradd -l -u 33333 -G sudo -md /home/gitpod -s /bin/bash -p gitpod gitpod && \
    # passwordless sudo for users in the 'sudo' group
    sed -i.bkp -e 's/%sudo\s\+ALL=(ALL\(:ALL\)\?)\s\+ALL/%sudo ALL=NOPASSWD:ALL/g' /etc/sudoers

# Switch to gitpod user
USER gitpod

# Install informative git for bash
RUN git clone https://github.com/magicmonty/bash-git-prompt.git ~/.bash-git-prompt --depth=1

# Set up .bashrc
WORKDIR /home/gitpod
RUN echo "GIT_PROMPT_ONLY_IN_REPO=1" >> ~/.bashrc && \
    echo "source \${HOME}/.bash-git-prompt/gitprompt.sh" >> ~/.bashrc && \
    echo "export DEPENDENCIES_DIR=${DEPENDENCIES_DIR}" >> ~/.bashrc && \
    echo "export PATH=\${PATH}:\${DEPENDENCIES_DIR}/install/bin" >> ~/.bashrc && \
    echo "export YARP_DATA_DIRS=\${DEPENDENCIES_DIR}/install/share/yarp:\${DEPENDENCIES_DIR}/install/share/iCub:\${DEPENDENCIES_DIR}/install/share/CER:\${DEPENDENCIES_DIR}/install/share/navigation:\${DEPENDENCIES_DIR}/install/share/ICUBcontrib" >> ~/.bashrc

# Switch back to root
USER root

# Make sure specific dirs are owned by gitpod user
RUN chown -R gitpod.gitpod ${DEPENDENCIES_DIR}

RUN rm -Rf /var/lib/apt/lists/*

# Launch bash from /workspace
WORKDIR /workspace
CMD ["bash"]
