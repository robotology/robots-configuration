set(appname CER01)

set(scripts CER.xml yarprobotinterface.ini general.xml yarpmotorgui.ini firmwareupdater.ini)

yarp_install(FILES ${scripts} DESTINATION ${ICUBCONTRIB_ROBOTS_INSTALL_DIR}/${appname})
yarp_install(DIRECTORY calibrators DESTINATION ${ICUBCONTRIB_ROBOTS_INSTALL_DIR}/${appname})
yarp_install(DIRECTORY wrappers DESTINATION ${ICUBCONTRIB_ROBOTS_INSTALL_DIR}/${appname})
yarp_install(DIRECTORY hardware DESTINATION ${ICUBCONTRIB_ROBOTS_INSTALL_DIR}/${appname})
yarp_install(DIRECTORY sensors  DESTINATION ${ICUBCONTRIB_ROBOTS_INSTALL_DIR}/${appname})
yarp_install(DIRECTORY camera   DESTINATION ${ICUBCONTRIB_ROBOTS_INSTALL_DIR}/${appname})

