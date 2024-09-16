/*
 * cxsys.c
 *
 *  Created on: Sep 18, 2020
 *      Author: Rodolfo.Ortega
 */



#include "sys_mon.hpp"
#include "rtsim.hpp"
#include <mutex>
#include "sys_logger.hpp"
#include "sys_tasks.hpp"
#include "sys_config.hpp"

//declare system state
system_state_T sys_state = sys_INACTIVE;
//fault warning variable, used to count faults in the system
static int warning_fault_ctr;

std::mutex sys_mtx;           // mutex for critical section

/**
 * Initialize OS
 */
void SystemInit(void) {

	warning_fault_ctr = 0;	

    SystemLog("Initializing OS");
	// init rtos
	OsInit();

    SystemLog("Initializing Tasks");
	// Initialize tasks and services
	SystemInitTasks();

	// change OS state
	sys_state = sys_INIT;
}

/**
 * Start OS
 */
void SystemStart(void) {

	sys_state = sys_RUNNING;

	SystemLog("Starting OS");
    // start OS
	OsStart();
}

void GetSystemState(system_state_T *state) {

	// lock mutex for critical section
	sys_mtx.lock();

	*state = sys_state;

	// unlock mutex
	sys_mtx.unlock();
}


void SetSystemException(system_exception_T exception) {
	if(exception == sys_Taskoverrun) {
		SystemLog("Task overrun");
		sys_state = sys_STOP;
	}

	if(exception == sys_Taskdelayed) {        
        warning_fault_ctr++;
		SystemLog("task delayed");
	}

	if(exception == sys_Restart) {
		sys_state = sys_INIT;
		SystemLog("Restarting system");
	}

	if(exception == sys_Halt) {
		SystemLog("system halt");
		sys_state = sys_STOP;
	}

}

/**
 * Monitor System
 this should be called every cycle for accurate monitoring
 */
void SystemMonitor(void) {
    // declare variables
    static int loop_ctr = 0;
    loop_ctr++;

    // monitor faults in the system
    if((loop_ctr%100) == 1) {

        // if there are more than 10 faults then stop the system
        if(warning_fault_ctr > 10) {
            sys_state = sys_STOP;
            SystemLog("tasks are out of sync, Stopping system...");
        }

        warning_fault_ctr = 0;
    }

}

/**
 * De-Initialize OS
 */
void SystemDeinit(void) {
	
    SystemDeInitTasks();
    sys_state = sys_INACTIVE;
    SystemLog("Deinitializing system");

}
