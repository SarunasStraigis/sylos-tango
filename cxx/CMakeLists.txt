cmake_minimum_required(VERSION 2.6)

cmake_policy(SET CMP0015 NEW)

project (laser-controller-device-server)

set(TANGO_HOME /usr/include/tango)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_C_COMPILER /usr/bin/gcc)

include_directories(${TANGO_HOME})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W -D_REENTRANT -pipe -fno-enforce-eh-specs -std=c++11")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -W -D_REENTRANT -pipe -fno-enforce-eh-specs")

set(LASER_CONTROLLER_COMMON_SOURCES
LaserController.cpp
LaserControllerClass.cpp
LaserControllerStateMachine.cpp
)

set(LASER_CONTROLLER_SOURCES
LaserControllerClassFactory.cpp
main.cpp
)

add_library(laser-controller-common SHARED ${LASER_CONTROLLER_COMMON_SOURCES})

add_executable(LaserControllerDS ${LASER_CONTROLLER_SOURCES})

target_link_libraries(LaserControllerDS tango log4tango COS4 omniORB4 omniDynamic4 omnithread laser-controller-common)
