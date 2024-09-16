#ifndef _DEVICE_TYPES_INCLUDED_
#define _DEVICE_TYPES_INCLUDED_

/*=============================================
		INCLUDES
==============================================*/
#include "system_types.hpp"
/*======================
		DEFINES
=======================*/
#define  _PIN_HIGH_  1

/*======================
		VARIABLES
=======================*/
typedef volatile uint32 encoderCounter_T;

/*======================
		FUNCTIONS
=======================*/
typedef enum drivers_response_T{
    driver_init_error = 0, // there was an error initialzing driver
    driver_lost_comm, // there was communication error or sensor/actuator has failure
	driver_ok  // everything is ok in driver
};

#endif //_DEVICE_TYPES_INCLUDED_