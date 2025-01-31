/*
 * app_swc1.c
 *
 *  Created on: Aug 20, 2020
 *      Author: Rodolfo.Ortega
 */

#include "system_types.hpp"
#include "main_app.hpp"
#include <iostream>

// include your headers here!!
#include "datapool.hpp"
#include "odometry.hpp"
#include "sys_mon.hpp"


void MainInit(void) {
	std::cout << "initializing app" << std::endl;
	// initialize throttle for motors
	DataPoolWriteRightMotorThrottle(60);
	DataPoolWriteLeftMotorThrottle(50);

	odometryInit();

}

static void rte_input_swc1(void) {
	//bind rte  signals with swc input signals.
	std::cout << "encoder 1: " <<  DataPoolReadEncoderCounter1() << std::endl;
	std::cout << "encoder 2: " <<  DataPoolReadEncoderCounter2() << std::endl;
}

static void rte_output_swc1(void) {
	//bind rte signals with swc output signals.

	
	std::cout << "right motor: " <<  DataPoolReadRightMotorThrottle() << std::endl;
	std::cout << "left motor: " <<  DataPoolReadLeftMotorThrottle() << std::endl;
}

void MainApp(void) {
	
    system_exception_T exception_local;

    // read inputs from rte
	rte_input_swc1();
	
	std::cout << "swc step" << std::endl; //  delete **
	odometryStep();
	

	if (DataPoolReadEgoDistance() > 1.0) {
            exception_local = sys_Halt; // halt system
            SetSystemException(exception_local);
			DataPoolWriteRightMotorThrottle(0);
			DataPoolWriteLeftMotorThrottle(0);
	}
	//write outputs to rte
	rte_output_swc1();
    
}


void MainDeInit(void) {
	std::cout << "de-initializing app" << std::endl;
}