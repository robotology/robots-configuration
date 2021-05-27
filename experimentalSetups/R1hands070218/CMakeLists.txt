set(appname R1SN000)

set(scripts CER_ALL.xml CER_ALL_fix.xml CER_ALL_fix_no_laser.xml CER_ALL_no_laser_skin.xml
            yarprobotinterface.ini general.xml yarpmotorgui.ini)

yarp_install(FILES ${scripts} DESTINATION ${CER_ROBOTS_INSTALL_DIR}/${appname})
yarp_install(DIRECTORY calibrators DESTINATION ${CER_ROBOTS_INSTALL_DIR}/${appname})
yarp_install(DIRECTORY wrappers DESTINATION ${CER_ROBOTS_INSTALL_DIR}/${appname})
yarp_install(DIRECTORY hardware DESTINATION ${CER_ROBOTS_INSTALL_DIR}/${appname})
yarp_install(DIRECTORY sensors  DESTINATION ${CER_ROBOTS_INSTALL_DIR}/${appname})

