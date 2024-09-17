#minmum version 
cmake_minimum_required(VERSION 3.13.4)

#project name
project(robo-broomba)

#include these directories
include_directories(core/inc)
include_directories(device/inc)
include_directories(gen)
include_directories(app/main)
include_directories(app/utilities)

#set (SOURCES cortexAlinux.cpp)

#find all source files
file(GLOB SOURCES "*.cpp", 
                  "core/src/*.cpp", 
                  "gen/*.cpp", 
                  "device/src/*.cpp",
                  "app/main/*.cpp",
                  "app/utilities/*.cpp")

#add the executables
add_executable(${PROJECT_NAME} ${SOURCES})

#link libraries needed
target_link_libraries(${PROJECT_NAME} pthread wiringPi)

