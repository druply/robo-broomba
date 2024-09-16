/*
 * sys_logger.cpp
 *
 *  Created on: Feb 5, 2022
 *      Author: Rodolfo.Ortega
 */

#include <mutex>

#include "sys_logger.hpp"
#include "sys_config.hpp"

std::mutex sys_log_mtx;

void DebugLog(double var, std::string text) {
    #ifdef ENABLE_DEBUG_LOGGER
    // lock mutex for critical section
	sys_log_mtx.lock();
    std::cout << text << var << std::endl;
    // unlock mutex
	sys_log_mtx.unlock();
    #endif
}

void DebugLog(std::string text) {
    #ifdef ENABLE_DEBUG_LOGGER
    // lock mutex for critical section
	sys_log_mtx.lock();
    std::cout << text << std::endl;
    // unlock mutex
	sys_log_mtx.unlock();
    #endif
}

void SystemLog(double var, std::string text) {
    #ifdef ENABLE_SYS_LOGGER
    // lock mutex for critical section
	sys_log_mtx.lock();
    std::cout << text << var << std::endl;
    	// unlock mutex
	sys_log_mtx.unlock();
    #endif
}

void SystemLog(std::string text) {
    #ifdef ENABLE_SYS_LOGGER
    // lock mutex for critical section
	sys_log_mtx.lock();
    std::cout << text << std::endl;
    	// unlock mutex
	sys_log_mtx.unlock();
    #endif
}