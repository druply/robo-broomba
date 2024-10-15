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


void MainInit(void) {
	std::cout << "initializing app" << std::endl;
	// initialize throttle for motors
	DataPoolWriteRightMotorThrottle(0);
	DataPoolWriteLeftMotorThrottle(0);
}

static void rte_input_swc1(void) {
	//bind rte  signals with swc input signals.
	std::cout << "encoder 1: " <<  DataPoolReadEncoderCounter1() << std::endl;
	std::cout << "encoder 2: " <<  DataPoolReadEncoderCounter2() << std::endl;
}

static void rte_output_swc1(void) {
	//bind rte signals with swc output signals.
	DataPoolWriteRightMotorThrottle(0);
	DataPoolWriteLeftMotorThrottle(0);
	
	std::cout << "right motor: " <<  DataPoolReadRightMotorThrottle() << std::endl;
	std::cout << "left motor2: " <<  DataPoolReadLeftMotorThrottle() << std::endl;
}

void MainApp(void) {
	
    
    // read inputs from rte
	rte_input_swc1();
	std::cout << "swc step" << std::endl;
	//write outputs to rte
	rte_output_swc1();
    
}


void MainDeInit(void) {
	std::cout << "de-initializing app" << std::endl;
}