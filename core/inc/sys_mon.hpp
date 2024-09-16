/*
 * sys_mon.hpp
 *
 *  Created on: Feb 4, 2022
 *      Author: Rodolfo.Ortega
 */

#ifndef CORE_SYS_MON_H_
#define CORE_SYS_MON_H_


typedef enum {
	sys_INACTIVE = 0,
	sys_INIT,
	sys_RUNNING,
	sys_STOP	
} system_state_T;

typedef enum {
	sys_Taskoverrun = 0,
	sys_Taskdelayed,
	sys_DrvError,
	sys_Restart,
	sys_Halt,
	sys_OK
} system_exception_T;

void SystemInit(void);
void SystemStart(void);
void SystemDeinit(void);
void GetSystemState(system_state_T *state);
void SetSystemException(system_exception_T exception);
void SystemMonitor(void);

#endif /* CORE_SYS_MON_H_ */
