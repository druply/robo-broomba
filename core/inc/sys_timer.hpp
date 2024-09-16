/*
 * cxrtos.hpp
 *
 *  Created on: Aug 18, 2021
 *      Author: Rodolfo.Ortega
 */

#ifndef SYS_TIMER_HPP_
#define SYS_TIMER_HPP_

void UpdateTimer(struct timespec *tmr);
double GetTimeElapsedUs(struct timespec *tmr1, struct timespec *tmr2);

//#define  ENABLE_SYS_TIMER

#endif /* SYS_TIMER_HPP_ */