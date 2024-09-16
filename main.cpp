//============================================================================
// Name        : main.cpp
// Author      : Rodolfo Ortega
// Version     :
// Copyright   : GNU License
// Description : Main file for strawberry framework
//============================================================================

//include headers
#include <iostream>
#include "sys_mon.hpp"


int main() {
	//declare system state
	static system_state_T state = sys_INACTIVE;
	//decalre system running
	static bool running = true;

	// Initialize system
	//SystemInit();

	//enter infitine loop while system is running
	while(running) {
		// get system state
		GetSystemState(&state);
		//choose funciton based on system state
		switch(state) {					
			case sys_INACTIVE:				
				// initialize system
				SystemInit();				
				break;
			
			case sys_INIT:
				// start system
				SystemStart();				
				break;
			
			case sys_STOP:
				// stop running system
				running = false;
				break;
			
			default:
				break;
		}
	}

	//de initialize system
	SystemDeinit();
	

	return 0;
}
