################################################################################
#                                                                              #
# Copyright (C) 2020 Fondazione Istitito Italiano di Tecnologia (IIT)          #
# All Rights Reserved.                                                         #
#                                                                              #
################################################################################

cmake_minimum_required(VERSION 3.12)
project(check-xml)

include(FetchContent)
FetchContent_Declare(
	pugixml
	GIT_REPOSITORY https://github.com/zeux/pugixml.git
	GIT_TAG        origin/master
)

FetchContent_GetProperties(pugixml)
if(NOT pugixml)
	FetchContent_Populate(pugixml)
	add_subdirectory(${pugixml_SOURCE_DIR} ${pugixml_BINARY_DIR})
endif()

find_package(YARP REQUIRED COMPONENTS os)
find_package(ICUBcontrib REQUIRED)
list(APPEND CMAKE_MODULE_PATH ${ICUBCONTRIB_MODULE_PATH})
include(ICUBcontribOptions)
include(ICUBcontribHelpers)
icubcontrib_set_default_prefix()

add_executable(${PROJECT_NAME})
target_sources(${PROJECT_NAME} PRIVATE src/check-xml.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE YARP::YARP_os pugixml::pugixml)

# install
install(
 TARGETS ${PROJECT_NAME}
 EXPORT ${CMAKE_PROJECT_NAME}
 LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
 ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
 RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
 PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

 file(GLOB schemas ${CMAKE_CURRENT_SOURCE_DIR}/schemas/*.xsd)
 yarp_install(FILES ${schemas} DESTINATION ${ICUBCONTRIB_CONTEXTS_INSTALL_DIR}/${PROJECT_NAME})