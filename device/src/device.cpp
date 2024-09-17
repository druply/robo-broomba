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
#include "datatypes.hpp"
#include "datapool.hpp"
#include "sys_mon.hpp"
#include "main_app.hpp"

bool init_error;
uint8_t state_curr = STATE_INIT;

void DeviceInit(void) {
    
    drivers_response_T init_res;
    std::cout << "device init" << std::endl;

    init_error = true; // set to fault by default
    
    // When initialize wiring failed, print message to screen
	if(wiringPiSetup() == -1) {
		SystemLog("error configuring wiringpi");
		//return WIRING_PI_ERROR; // stop system
	}
    else {
        SystemLog("wiringpi configured");
    }

    if ((encoderDrvInit() == driver_init_error)||
        (motorDrvInit()   == driver_init_error))  {
            init_error = true; // error occured
            state_curr = STATE_INIT_ERROR; //enter init error state
    }
    else {
        init_error = false;
        SystemLog("Drivers initialized succesfully");
        state_curr = STATE_APP_INIT; // initialize apps
    }

    // set direction of motors
    setLeftMotorForward();
    setRightMotorForward();
    
}

static void readSensorData(void) {
    DataPoolWriteEncoderCounter1(encoder1_ctr);
    DataPoolWriteEncoderCounter2(encoder2_ctr);

}

static void writeSensorData(void) {
    setRightMotorThrottle( DataPoolReadRightMotorThrottle() );
    setLeftMotorThrottle ( DataPoolReadLeftMotorThrottle()  );
}


void DeviceStep(void) {
    
    static uint8_t ctr_tmp = 0;
    system_exception_T exception_local;

    switch(state_curr) {
        
        case STATE_INIT:
          DeviceInit();
          if(init_error == true) {
            state_curr = STATE_INIT_ERROR;
            SystemLog("Initialization error, restarting system");
          } 
          else {
            state_curr = STATE_APP_INIT; // initialize apps
          }
          break;

        case STATE_INIT_ERROR:
          ctr_tmp++;
          if (ctr_tmp == 150) {
            state_curr = STATE_INIT; // restart state machine
            exception_local = sys_Restart; // restart system
            SetSystemException(exception_local);
          }
          break;

        case STATE_RUN:
            readSensorData(); // get sensor data
            MainApp(); // run main app
            writeSensorData(); // wrtie sensor/actuator data

            break;

        case STATE_APP_INIT:
            MainInit(); // initialize app
            state_curr = STATE_RUN; // run apps
            break;

        default:
          break;

    }

}

void DeviceDeInit(void) {
    MainDeInit();
    std::cout << "device deinit" << std::endl;
}