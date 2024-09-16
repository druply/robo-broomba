/*
 * encoder_drv.cpp
 * this file defines the gpio configuration raspberry pi 4
 */

/*=============================================
		INCLUDES
==============================================*/


#include <wiringPi.h>
#include <wiringPiI2C.h>
#include "sys_logger.hpp"

#include "encoder_drv.hpp"
/*======================
		DEFINES
=======================*/


/*======================
		VARIABLES
=======================*/
encoderCounter_T encoder1_ctr;
encoderCounter_T encoder2_ctr;


/*======================
		FUNCTIONS
=======================*/

/**
* Interrupt function for
* encoder 1
*/
void encoder1Int(void) {
    
	int encoder1_pin;
	encoder1_pin = digitalRead(_ENCODER1_IN);

	//only increase if the input is in the right logical level
	if(encoder1_pin == _PIN_HIGH_) {
		// increase encoder counter
		encoder1_ctr++;
	}
	
}

/**
* Interrupt function for
* encoder 2
*/
void encoder2Int(void) {
    
	int encoder2_pin;
	encoder2_pin = digitalRead(_ENCODER2_IN);
	
	//only increase if the input is in the right logical level
	if(encoder2_pin == _PIN_HIGH_) {
		// increase encoder counter
    	encoder2_ctr++;

	}
}

drivers_response_T encoderDrvInit(void) {
	bool init_error = false;

	// initialize pins
	pinMode(_ENCODER1_IN, INPUT); // Set Pin as input to read value from it.
	pinMode(_ENCODER2_IN, INPUT); // Set Pin as input to write value from it.



    if (wiringPiISR(_ENCODER2_IN, INT_EDGE_RISING, &encoder2Int) < 0 ) {
        SystemLog("error configuring isr");
		init_error = true;
		//return WIRINGPI_ISR_ERROR;
    }
	else {
		SystemLog("encoder 2 configured");
	}

	// set Pin to generate an interrupt on transition from low to high
    if (wiringPiISR(_ENCODER1_IN, INT_EDGE_RISING, &encoder1Int) < 0 ) {
      SystemLog("error configuring isr");
	  init_error = true;
	  //return WIRINGPI_ISR_ERROR;
    }
	else {
		SystemLog("encoder 1 configured");
	}

	if (init_error == false) {
		return driver_ok;
	}
	else {
		return driver_init_error;
	}
}