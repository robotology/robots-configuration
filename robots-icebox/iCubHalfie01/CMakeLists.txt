set(appname iCubHalfie01)

file(GLOB xml ${CMAKE_CURRENT_SOURCE_DIR}/*.xml)
file(GLOB ini ${CMAKE_CURRENT_SOURCE_DIR}/*.ini)
set(whatsleft firmwareUpdate.txt)

yarp_install(FILES ${xml} DESTINATION ${ICUBCONTRIB_ROBOTS_INSTALL_DIR}/${appname})
yarp_install(FILES ${ini} DESTINATION ${ICUBCONTRIB_ROBOTS_INSTALL_DIR}/${appname})
yarp_install(FILES ${whatsleft} DESTINATION ${ICUBCONTRIB_ROBOTS_INSTALL_DIR}/${appname})
yarp_install(DIRECTORY calibrators DESTINATION ${ICUBCONTRIB_ROBOTS_INSTALL_DIR}/${appname})
yarp_install(DIRECTORY wrappers DESTINATION ${ICUBCONTRIB_ROBOTS_INSTALL_DIR}/${appname})
yarp_install(DIRECTORY hardware DESTINATION ${ICUBCONTRIB_ROBOTS_INSTALL_DIR}/${appname})
yarp_install(DIRECTORY camera DESTINATION ${ICUBCONTRIB_ROBOTS_INSTALL_DIR}/${appname})
