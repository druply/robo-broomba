/*
 * sys_mon.hpp
 *
 *  Created on: Feb 4, 2022
 *      Author: Rodolfo.Ortega
 */

#ifndef CORE_SYS_LOGGER_H_
#define CORE_SYS_LOGGER_H_

#include <iostream>

//#define  ENABLE_DEBUG_LOGGER
//#define  ENABLE_SYS_LOGGER

void DebugLog(double var, std::string text);
void DebugLog(std::string text);
void SystemLog(double var, std::string text);
void SystemLog(std::string text);

#endif /* CORE_SYS_LOGGER_H_ */