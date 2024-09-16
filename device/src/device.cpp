/*
 * device.cpp
 * this file defines the device interface for the robo cleaner
 * using the raspberry pi 4
 */
#include "device.hpp"
#include "encoder_drv.hpp"
#include <wiringPi.h>
#include "sys_logger.hpp"
#include <iostream>

#include "encoder_drv.hpp"
#include "motor_diff_drv.hpp"

bool init_error = false;

void DeviceInit(void) {
    
    drivers_response_T init_res;
    std::cout << "device init" << std::endl;
    
    // When initialize wiring failed, print message to screen
	if(wiringPiSetup() == -1) {
		SystemLog("error configuring wiringpi");
		//return WIRING_PI_ERROR; // stop system
	}
    else {
        SystemLog("wiringpi configured");
    }

    init_res = encoderDrvInit();

    if (init_res == driver_init_error) {
        init_error = true;
    }
    init_res = motorDrvInit();
    
    if (init_res == driver_init_error) {
        init_error = true;
    }
    //setRightMotorThrottle(40);
    setLeftMotorForward();
    setLeftMotorThrottle(100);
}

void DeviceStep(void) {
    std::cout << " encoder 1: " << encoder1_ctr <<std::endl;
    std::cout << " encoder 2: " << encoder2_ctr <<std::endl;
}

void DeviceDeInit(void) {
    std::cout << "device deinit" << std::endl;
}