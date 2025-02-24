/*
 * app_swc1.c
 *
 *  Created on: Aug 20, 2020
 *      Author: Rodolfo.Ortega
 */

#include "system_types.hpp"
#include "main_app.hpp"

// include your headers here!!
#include "datapool.hpp"
#include "odometry.hpp"
#include "sys_mon.hpp"
#include "main_test.hpp"
#include "test_cfg.hpp"
#include "state_handler.hpp"
#include "motion_monitor.hpp"
#include "motion_control.hpp"

/*
Initialize main app
*/
void MainInit(void) {

	stateHandlerInit(); // initialize state handler
	testInit(); // initalize testinit 
	motionControlInit();
	
	// initialize throttle for motors
	DataPoolWriteRightMotorThrottle(0);
	DataPoolWriteLeftMotorThrottle(0);

	odometryInit();

}

static void rte_input_swc1(void) {
	//bind rte  signals with swc input signals.

}

static void rte_output_swc1(void) {
	//bind rte signals with swc output signals.

}

/*
Main  application function
*/
void MainApp(void) {

	#ifndef ENABLE_TEST
    
	// read inputs from rte
	rte_input_swc1();

	#endif

    #ifdef ENABLE_TEST
		// run main test app
		mainTest();

	#else
		// run state handler
		stateHandlerStep();
        // motion control
		motionControlStep();

	#endif


	#ifndef ENABLE_TEST
	//write outputs to rte
	rte_output_swc1();    

	#endif
}


void MainDeInit(void) {

}