set(appname iCubNottingham01)

set(scripts icub_all.xml icub_all_inertials.xml yarprobotinterface.ini firmwareupdater.ini network.${appname}.xml general.xml iKinGazeCtrl.ini icubEyes.ini)

yarp_install(FILES ${scripts} DESTINATION ${ICUBCONTRIB_ROBOTS_INSTALL_DIR}/${appname})
yarp_install(DIRECTORY calibrators DESTINATION ${ICUBCONTRIB_ROBOTS_INSTALL_DIR}/${appname})  
yarp_install(DIRECTORY cartesian DESTINATION ${ICUBCONTRIB_ROBOTS_INSTALL_DIR}/${appname})
yarp_install(DIRECTORY wrappers DESTINATION ${ICUBCONTRIB_ROBOTS_INSTALL_DIR}/${appname})
yarp_install(DIRECTORY hardware DESTINATION ${ICUBCONTRIB_ROBOTS_INSTALL_DIR}/${appname}) 
yarp_install(DIRECTORY camera DESTINATION ${ICUBCONTRIB_ROBOTS_INSTALL_DIR}/${appname}) 


