set(appname iCubNancy01)

set(scripts icub_all.xml yarprobotinterface.ini general.xml iKinGazeCtrl.ini icubEyes.ini pf3dTracker.ini cartesianSolver.ini)

yarp_install(FILES ${scripts} DESTINATION ${ICUBCONTRIB_ROBOTS_INSTALL_DIR}/${appname})
yarp_install(FILES ${dragonFly} DESTINATION ${ICUBCONTRIB_ROBOTS_INSTALL_DIR}/${appname})
yarp_install(DIRECTORY calibrators DESTINATION ${ICUBCONTRIB_ROBOTS_INSTALL_DIR}/${appname})  
yarp_install(DIRECTORY cartesian DESTINATION ${ICUBCONTRIB_ROBOTS_INSTALL_DIR}/${appname})
yarp_install(DIRECTORY wrappers DESTINATION ${ICUBCONTRIB_ROBOTS_INSTALL_DIR}/${appname})
yarp_install(DIRECTORY hardware DESTINATION ${ICUBCONTRIB_ROBOTS_INSTALL_DIR}/${appname}) 
yarp_install(DIRECTORY camera DESTINATION ${ICUBCONTRIB_ROBOTS_INSTALL_DIR}/${appname}) 


