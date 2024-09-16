#minmum version 
cmake_minimum_required(VERSION 3.13.4)

#project name
project(strawberry)

#include these directories
include_directories(core/inc)
include_directories(app/inc)
include_directories(device/inc)
include_directories(gen)

#set (SOURCES cortexAlinux.cpp)

#find all source files
file(GLOB SOURCES "*.cpp", "core/src/*.cpp", "gen/*.cpp", "app/src/*.cpp", "device/src/*.cpp")

#add the executables
add_executable(${PROJECT_NAME} ${SOURCES})

#link libraries needed
target_link_libraries(${PROJECT_NAME} pthread wiringPi)

