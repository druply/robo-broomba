/*
 * rtsim.c
 *
 *  Created on: Aug 22, 2020
 *      Author: Rodolfo.Ortega
 */

#include <time.h>
#include <thread>
#include <mutex>
#include <chrono>

#include "rtsim.hpp"
#include "sys_mon.hpp"
#include "sys_tasks.hpp"
#include "sys_timer.hpp"
#include "sys_config.hpp"

// test headers

struct timespec rt_loop, rt_loop1, rt_loop2, rt_loop3;


void OsInit(void) {
	// init code
}


static void Thread1(void) {
	double loop_time = 0.0;
	double previous_loop = 0.0;

	UpdateTimer(&rt_loop1);
	previous_loop = (rt_loop1.tv_sec) * 1e9 + (rt_loop1.tv_nsec);
	system_state_T os_state = sys_RUNNING;
	system_exception_T exception = sys_Taskdelayed;

	GetSystemState(&os_state);

	do {
		// get current clock timestamp
		UpdateTimer(&rt_loop1);

		// get time difference betwee current timesampt and previous timestamp
		loop_time = (rt_loop1.tv_sec) * 1e9 + (rt_loop1.tv_nsec);
		loop_time = loop_time - previous_loop;

		// if difference is greater than 10ms then execute real time simulator
		if (loop_time >= MAIN_CYCLE_nS) {

		  if(loop_time > (MAIN_CYCLE_nS*1.5)) {
				SetSystemException(exception);
		  }
		  // get clock timestamp
		  UpdateTimer(&rt_loop1);
		  //update previous loop time
	      previous_loop = (rt_loop1.tv_sec) * 1e9 + (rt_loop1.tv_nsec);

		  // call real time simulator
		  #if SYS_TASKS_NUM_OF_THREADS > 1
		  SystemTask1();
		  #endif
		 }

		GetSystemState(&os_state);
	} while(os_state == sys_RUNNING);
}

static void Thread2(void) {
	double loop_time = 0.0;
	double previous_loop = 0.0;

	UpdateTimer(&rt_loop2);
	previous_loop = (rt_loop2.tv_sec) * 1e9 + (rt_loop2.tv_nsec);
	system_state_T os_state = sys_RUNNING;
	GetSystemState(&os_state);

	do {
		// get current clock timestamp
		UpdateTimer(&rt_loop2);

		// get time difference betwee current timesampt and previous timestamp
		loop_time = (rt_loop2.tv_sec) * 1e9 + (rt_loop2.tv_nsec);
		loop_time = loop_time - previous_loop;

		// if difference is greater than 10ms then execute real time simulator
		if (loop_time >= MAIN_CYCLE_nS) {
		  // get clock timestamp
		  UpdateTimer(&rt_loop2);
		  //update previous loop time
	      previous_loop = (rt_loop2.tv_sec) * 1e9 + (rt_loop2.tv_nsec);
		  // call real time simulator
		  #if SYS_TASKS_NUM_OF_THREADS > 2
		  SystemTask2();
		  #endif

		 }

		GetSystemState(&os_state);
	} while(os_state == sys_RUNNING);
}


static void Thread3(void) {

	double loop_time = 0.0;
	double previous_loop = 0.0;

	UpdateTimer(&rt_loop3);
	previous_loop = (rt_loop3.tv_sec) * 1e9 + (rt_loop3.tv_nsec);
	system_state_T os_state = sys_RUNNING;
	GetSystemState(&os_state);

	do {
		// get current clock timestamp
		UpdateTimer(&rt_loop3);

		// get time difference betwee current timesampt and previous timestamp
		loop_time = (rt_loop3.tv_sec) * 1e9 + (rt_loop3.tv_nsec);
		loop_time = loop_time - previous_loop;

		// if difference is greater than 10ms then execute real time simulator
		if (loop_time >= MAIN_CYCLE_nS) {
		  // get clock timestamp
		  UpdateTimer(&rt_loop3);
		  //update previous loop time
	      previous_loop = (rt_loop3.tv_sec) * 1e9 + (rt_loop3.tv_nsec);
		  // call real time simulator
		  #if SYS_TASKS_NUM_OF_THREADS > 3
		  SystemTask3();
		  #endif

		 }

		GetSystemState(&os_state);
	} while(os_state == sys_RUNNING);
}


static void NrtThread0(void) {
	system_state_T os_state = sys_RUNNING;
	GetSystemState(&os_state);

	do {
	  // call thread
	  #if SYS_NUM_OF_NRT_THREADS_ > 0
		NrtSystemTask0();
	  #endif

	  GetSystemState(&os_state);
	} while(os_state == sys_RUNNING);
}


static void NrtThread1(void) {
	system_state_T os_state = sys_RUNNING;
	GetSystemState(&os_state);

	do {
	  // call thread
	  #if SYS_NUM_OF_NRT_THREADS_ > 1
		NrtSystemTask1();
	  #endif
	  GetSystemState(&os_state);
	} while(os_state == sys_RUNNING);
}

static void TmpThread0(void) {
	// call thread and finish
	//cxosThread_tmp0();
}


static void TmpThread1(void) {
	// call thread and finish
	//cxosThread_tmp1();
}

void OsStart(void) {
	double loop_time = 0.0;
	double previous_loop = 0.0;

	UpdateTimer(&rt_loop);
	previous_loop = (rt_loop.tv_sec) * 1e9 + (rt_loop.tv_nsec);
	system_state_T os_state = sys_RUNNING;
	system_exception_T exception = sys_Taskdelayed;

	GetSystemState(&os_state);

	//start threads
	#if SYS_TASKS_NUM_OF_THREADS > 1
	std::thread thread1(Thread1);
	thread1.detach();
	#endif

	#if SYS_TASKS_NUM_OF_THREADS > 2
	std::thread thread2(Thread2);
	thread2.detach();
	#endif

	#if SYS_TASKS_NUM_OF_THREADS > 3
	std::thread thread3(Thread3);
	thread3.detach();
	#endif


	#if SYS_NUM_OF_NRT_THREADS_ > 0
	std::thread thread10(NrtThread0);
	thread10.detach();
	#endif

	#if SYS_NUM_OF_NRT_THREADS_ > 1
	std::thread thread11(NrtThread1);
	thread11.detach();
	#endif

	#if SYS_NUM_OF_NRT_THREADS_ > 0
	std::thread thread20(TmpThread0);
	thread20.detach();
	#endif

	#if SYS_NUM_OF_NRT_THREADS_ > 1
	std::thread thread21(TmpThread1);
	thread21.detach();
	#endif

	do {
		// get current clock timestamp
		UpdateTimer(&rt_loop);

		// get time difference betwee current timesampt and previous timestamp
		loop_time = (rt_loop.tv_sec) * 1e9 + (rt_loop.tv_nsec);
		loop_time = loop_time - previous_loop;

		// if difference is greater than 10ms then execute real time simulator
		if (loop_time>=MAIN_CYCLE_nS) {

			// if execution took more than 50% of main cycle time then set an exception
		  if(loop_time > (MAIN_CYCLE_nS*1.5)) {
				SetSystemException(exception);
		  }
		  // get clock timestamp
		  UpdateTimer(&rt_loop);
		  //update previous loop time
	      previous_loop = (rt_loop.tv_sec) * 1e9 + (rt_loop.tv_nsec);

		  // call real time simulator
		  SystemTask0();
		  SystemMonitor();

		 }
		GetSystemState(&os_state);
	} while(os_state == sys_RUNNING);

}
