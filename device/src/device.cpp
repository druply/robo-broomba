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
#include "mpu9250_drv.hpp"
#include "datatypes.hpp"
#include "datapool.hpp"
#include "sys_mon.hpp"
#include "main_app.hpp"

bool init_error;
device_status_E state_curr;

void DeviceInit(void) {
    
    drivers_response_E init_res;
    std::cout << "device init" << std::endl;

    init_error = true; // set to fault by default
    state_curr = device_status_E::init; // initializing device
    
    // When initialize wiring failed, print message to screen
	if(wiringPiSetup() == -1) {
		SystemLog("error configuring wiringpi");
		//return WIRING_PI_ERROR; // stop system
	}
    else {
        SystemLog("wiringpi configured");
    }
    // Initializing drivers 
    if ((encoderDrvInit() == drivers_response_E::init_error)||
        (motorDrvInit()   == drivers_response_E::init_error) ||
        (mpu9250Init() == drivers_response_E::init_error))  {
            init_error = true; // error occured
            state_curr = device_status_E::error; //enter init error state
    }
    else {
        init_error = false;
        SystemLog("Drivers initialized succesfully");
        state_curr = device_status_E::app_init; // initialize apps
    }

    // set direction of motors
    //setLeftMotorBackward();
    //setRightMotorBackward();

    setLeftMotorForward();
    setRightMotorForward();
    
}

static void readSensorData(void) {
    /* Write encoder 1 value to datapool */
    DataPoolWriteEncoderCounter1(encoder1_ctr);
    /* Write encoder 2 value to datapool */
    DataPoolWriteEncoderCounter2(encoder2_ctr);
    /* Write imu data to datapool */
    DataPoolWriteImuData(&imu_data);

}

static void writeSensorData(void) {
    setRightMotorThrottle( DataPoolReadRightMotorThrottle() );
    setLeftMotorThrottle ( DataPoolReadLeftMotorThrottle()  );
}

/*
Main function for device 
*/
void DeviceStep(void) {
    
    static uint8_t ctr_tmp = 0;
    system_exception_T exception_local;

    switch(state_curr) {
        
        case device_status_E::init:
          DeviceInit();
          if(init_error == true) {
            state_curr = device_status_E::error;
            SystemLog("Initialization error, restarting system");
          } 
          else {
            state_curr = device_status_E::app_init; // initialize apps
          }
          break;

        case device_status_E::error:
          ctr_tmp++;
          if (ctr_tmp == 150) {
            state_curr = device_status_E::init; // restart state machine
            exception_local = sys_Restart; // restart system
            SetSystemException(exception_local);
          }
          break;

        case device_status_E::ready :
            mpu9250Step(); // read IMU data
            readSensorData(); // get sensor data

            MainApp(); // run main app
            
            writeSensorData(); // wrtie sensor/actuator data

            break;

        case device_status_E::app_init :
            MainInit(); // initialize app
            state_curr = device_status_E::ready; // run apps
            break;

        default:
          break;

    }

}

/*
Non real time task to read encoders in a loop
*/
void DeviceLoop(void) {
 
 if( (DataPoolReadRightMotorThrottle() != 0) || (DataPoolReadLeftMotorThrottle()!= 0) ) {
    readEncoders();
 }

}

void DeviceDeInit(void) {
    MainDeInit();
    std::cout << "device deinit" << std::endl;
}