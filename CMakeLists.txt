# Copyright: (C) 2016 iCub Facility - Istituto Italiano di Tecnologia
# Authors: Ugo Pattacini
# CopyPolicy: Released under the terms of the GNU GPL v2.0.

cmake_minimum_required(VERSION 3.5)
project(robots-configuration)

find_package(YARP REQUIRED)
find_package(ICUBcontrib REQUIRED)

list(APPEND CMAKE_MODULE_PATH ${YARP_MODULE_PATH})
list(APPEND CMAKE_MODULE_PATH ${ICUBCONTRIB_MODULE_PATH})

include(YarpInstallationHelpers)
include(ICUBcontribOptions)
include(ICUBcontribHelpers)

option(INSTALL_ALL_ROBOTS "Enable installation of all robots" OFF)
set(ROBOT_NAME "$ENV{YARP_ROBOT_NAME}" CACHE PATH "Name of your robot")
set(ROBOT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/${ROBOT_NAME}")

icubcontrib_set_default_prefix()

if(INSTALL_ALL_ROBOTS)
    # List the subdirectories (http://stackoverflow.com/questions/7787823/cmake-how-to-get-the-name-of-all-subdirectories-of-a-directory)
    macro(SUBDIRLIST result curdir)
        file(GLOB children RELATIVE ${curdir} ${curdir}/*)
        set(dirlist "")
        foreach(child ${children})
            if(IS_DIRECTORY ${curdir}/${child})
                list(APPEND dirlist ${child})
            endif()
        endforeach()
        set(${result} ${dirlist})
    endmacro()

    # Get list of models
    subdirlist(subdirs ${CMAKE_CURRENT_SOURCE_DIR})

    # Install each model
    foreach (dir ${subdirs})
        message(STATUS "Checking if ${dir}/CMakeLists.txt exists")
        if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/${dir}/CMakeLists.txt)
            message(STATUS "Exists")
            add_subdirectory(${dir})
        else()
            message(STATUS "Does not")
        endif()
    endforeach()
else()
    if(ROBOT_NAME)
        if(IS_DIRECTORY ${ROBOT_DIR})
            add_subdirectory(${ROBOT_NAME})
        endif()
    endif()
endif()

# setup symbolic link (on UNIX...)
if("${ROBOT_NAME}" STREQUAL "")
    message(STATUS "No robot name")
else()
    if(EXISTS ${ROBOT_DIR})
        if(UNIX)
            message(STATUS "Setting up symbolic link for ${ROBOT_NAME}")
            install(CODE "execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_INSTALL_PREFIX}/${ICUBCONTRIB_ROBOTS_INSTALL_DIR}/${ROBOT_NAME})\n
                          execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_INSTALL_PREFIX}/${ICUBCONTRIB_ROBOTS_INSTALL_DIR}/${ROBOT_NAME}\n
                                                                                     ${CMAKE_INSTALL_PREFIX}/${ICUBCONTRIB_ROBOTS_INSTALL_DIR}/default)")
            add_custom_target(robotSymLink ALL COMMAND ${CMAKE_COMMAND} -E create_symlink ${CMAKE_BINARY_DIR}/${ICUBCONTRIB_ROBOTS_INSTALL_DIR}/${ROBOT_NAME}
                                                                                          ${CMAKE_BINARY_DIR}/${ICUBCONTRIB_ROBOTS_INSTALL_DIR}/default
                                           DEPENDS ${CMAKE_BINARY_DIR}/${ICUBCONTRIB_ROBOTS_INSTALL_DIR}/${ROBOT_NAME})
        else()
            message(STATUS "Cannot set up symbolic link for ${ROBOT_NAME} on this OS, please set the YARP_ROBOT_NAME environment variable to ${ROBOT_NAME}")
        endif()
    else()
        message(WARNING "ROBOT_NAME is set to ${ROBOT_NAME} but the ${ROBOT_DIR} directory does not exist")
    endif()
endif()

icubcontrib_add_uninstall_target()
