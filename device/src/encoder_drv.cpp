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
#include <iostream>
/*======================
		DEFINES
=======================*/


/*======================
		VARIABLES
=======================*/
encoderCounter_T encoder1_ctr; // counter for wheel 1
encoderCounter_T encoder2_ctr; // counter for wheel 2

static unsigned int prev_encoder1_pin;
static unsigned int prev_encoder2_pin;
/*======================
		FUNCTIONS
=======================*/

/**
* Interrupt function for
* encoder 1
* This function gets called everytime there is an interrupt
* caused by the encoder
*/
void encoder1Int(void) {
    
	int encoder1_pin;
	//int encoder2_pin;
	encoder1_pin = digitalRead(_ENCODER1_IN);
	//encoder2_pin = digitalRead(_ENCODER2_IN);

	//only increase if the input is in the right logical level
	//if(encoder1_pin == _PIN_HIGH_) {
		// increase encoder counter
		encoder1_ctr++;
		SystemLog("encoder 1 interrupt");
	//}
	/*
		if(encoder2_pin == _PIN_HIGH_) {
		// increase encoder counter
    	encoder2_ctr++;

	}
	*/
	
}

/**
* Interrupt function for
* encoder 2
* This function gets called everytime there is an interrupt
* caused by the encoder
*/
void encoder2Int(void) {
    
	//int encoder1_pin;
	int encoder2_pin;
	encoder2_pin = digitalRead(_ENCODER2_IN);
	//encoder1_pin = digitalRead(_ENCODER1_IN);
	
	//only increase if the input is in the right logical level
	//if(encoder2_pin == _PIN_HIGH_) {
		// increase encoder counter
    	encoder2_ctr++;
		SystemLog("encoder 2 interrupt");

	//}
/*
		if(encoder1_pin == _PIN_HIGH_) {
		// increase encoder counter
		encoder1_ctr++;
	}
	*/
}

unsigned int readDigitalFilter1(void) {
	static unsigned int encoder1_tmp_prev = 0U;
    unsigned int encoder1_tmp;
	static unsigned int encoder1_ctr = 0;


    encoder1_tmp = digitalRead(_ENCODER1_IN);

	if (encoder1_tmp == 1U) {
		encoder1_ctr++;
		if(encoder1_ctr == ENCODER_DELAY_READ) {
            encoder1_ctr=0;
			encoder1_tmp_prev = 1U;
			
		}
	}
	else {
		encoder1_ctr=0;
		encoder1_tmp_prev = 0U;
	}

	return encoder1_tmp_prev;

}

unsigned int readDigitalFilter2(void) {
	static unsigned int encoder2_tmp_prev = 0U;
    unsigned int encoder2_tmp;
	static unsigned int encoder2_ctr = 0;


    encoder2_tmp = digitalRead(_ENCODER2_IN);

	if (encoder2_tmp == 1U) {
		encoder2_ctr++;
		if(encoder2_ctr == ENCODER_DELAY_READ) {
            encoder2_ctr=0;
			encoder2_tmp_prev = 1U;
			
		}
	}
	else {
		encoder2_ctr=0;
		encoder2_tmp_prev = 0U;
	}

	return encoder2_tmp_prev;

}

void readEncoders(void) {
	unsigned int encoder1_pin;
	unsigned int encoder2_pin;
	

	encoder1_pin = digitalRead(_ENCODER1_IN);
	encoder2_pin = digitalRead(_ENCODER2_IN);

	if(encoder2_pin != prev_encoder2_pin) {

		if(encoder2_pin == _PIN_HIGH_) { 
			// increase encoder counter
    		encoder2_ctr++;
			//std::cout << "encoder2_ctr: " << encoder2_ctr << std::endl;
			//SystemLog("encoder 2 interrupt");
		}
		else {

		}
		prev_encoder2_pin = encoder2_pin;
		//std::cout << "encoder2: " << encoder2_pin << std::endl;
	}

	if(encoder1_pin != prev_encoder1_pin) {
			if(encoder1_pin == _PIN_HIGH_) { 
				// increase encoder counter
				encoder1_ctr++;
				//std::cout << "encoder1_ctr: " << encoder1_ctr << std::endl;
				//SystemLog("encoder 1 interrupt");
			}
			prev_encoder1_pin = encoder1_pin;
			//std::cout << "encoder1: " << encoder1_pin << std::endl;
	}
}

drivers_response_E encoderDrvInit(void) {
	bool init_error = false;

	// initialize pins
	pinMode(_ENCODER1_IN, INPUT); // Set Pin as input to read value from it.
	pinMode(_ENCODER2_IN, INPUT); // Set Pin as input to write value from it.

    encoder1_ctr = 0;
	encoder2_ctr = 0;

	prev_encoder1_pin = digitalRead(_ENCODER1_IN);
	prev_encoder2_pin = digitalRead(_ENCODER2_IN);

    /*
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
    */
   
	if (init_error == false) {
		return drivers_response_E::ok;
	}
	else {
		return drivers_response_E::init_error;
	}
}