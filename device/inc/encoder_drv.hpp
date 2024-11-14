#ifndef _ENCODER_DRV_INCLUDED_
#define _ENCODER_DRV_INCLUDED_

/*=============================================
		INCLUDES
==============================================*/
#include "device_types.hpp"

/*======================
		DEFINES
=======================*/
// define pins to be used
#define  _ENCODER1_IN	    0 // 17 BCM, 0 wiring
#define  _ENCODER2_IN	    1 // 18 BCM, 1 wiring

/*======================
		VARIABLES
=======================*/
extern encoderCounter_T encoder1_ctr;
extern encoderCounter_T encoder2_ctr;

/*======================
		FUNCTIONS
=======================*/
drivers_response_T encoderDrvInit(void);
void readEncoders(void);
#endif // _ENCODER_DRV_INCLUDED_