/*
 * sys_timer.c
 *
 *  Created on: Aug 22, 2020
 *      Author: Rodolfo.Ortega
 */
#include <mutex>
#include "sys_timer.hpp"

std::mutex rtsim_mtx;           // mutex for critical section

void UpdateTimer(struct timespec *tmr) {
	// lock mutex for critical section
	rtsim_mtx.lock();
	//std::thread::id this_id = std::this_thread::get_id();
	clock_gettime(CLOCK_MONOTONIC, tmr);
	//std::cout << "thread " << this_id << " tmr: "<< tmr << std::endl;;
	// unlock mutex
	rtsim_mtx.unlock();
}


double GetTimeElapsedUs(struct timespec *tmr1, struct timespec *tmr2) {
    double timer_init, timer_end, time_elapsed;
    
    timer_init = (tmr1->tv_sec) * 1e9 + (tmr1->tv_nsec);
    timer_end = (tmr2->tv_sec) * 1e9 + (tmr2->tv_nsec);

    time_elapsed = (timer_end - timer_init)/1000;

    return time_elapsed;
}