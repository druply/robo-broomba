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


void MainInit(void) {
	// initialize throttle for motors
	DataPoolWriteRightMotorThrottle(60);
	DataPoolWriteLeftMotorThrottle(60);

	odometryInit();

}

static void rte_input_swc1(void) {
	//bind rte  signals with swc input signals.

}

static void rte_output_swc1(void) {
	//bind rte signals with swc output signals.

}

void MainApp(void) {

	#ifndef ENABLE_TEST
    
	// read inputs from rte
	rte_input_swc1();

	#endif

    #ifdef ENABLE_TEST
		// run main test app
		mainTest();

	#else
		// run main app

	#endif


	#ifndef ENABLE_TEST
	//write outputs to rte
	rte_output_swc1();    

	#endif
}


void MainDeInit(void) {

}