/*
 * motor_diff_drv.cpp
 * this file defines the motor driver configuration for
 * the robo cleaner using the raspberry pi 4
 */

/*=============================================
		INCLUDES
==============================================*/
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include "motor_diff_drv.hpp"
#include "sys_logger.hpp"

/*======================
		DEFINES
=======================*/


/*======================
		VARIABLES
=======================*/
int motors_i2c;

/*======================
		FUNCTIONS
=======================*/

//! Set the frequency of PWM
/*!
 \param freq desired frequency. 40Hz to 1000Hz using internal 25MHz oscillator.
 */
void setPWMFreq(int freq) {

	uint8_t prescale_val = (CLOCK_FREQ / 4096 / freq)  - 1;

	#ifndef _WIN32
	wiringPiI2CWriteReg8(motors_i2c, MODE1, 0x10); //sleep

	wiringPiI2CWriteReg8(motors_i2c, PRE_SCALE, prescale_val); // multiplyer for PWM frequency

	wiringPiI2CWriteReg8(motors_i2c, MODE1, 0x80); // restart

	wiringPiI2CWriteReg8(motors_i2c, MODE2, 0x04); // totem pole (default)
	#endif
}


//! PWM a single channel with custom on time
/*!
 \param led channel (1-16) to set PWM value for
 \param on_value 0-4095 value to turn on the pulse
 \param off_value 0-4095 value to turn off the pulse
 */
void setPWM2(uint8_t led, int on_value, int off_value) {

	#ifndef _WIN32
	wiringPiI2CWriteReg8(motors_i2c, LED0_ON_L + LED_MULTIPLYER * (led - 1), on_value & 0xFF);

	wiringPiI2CWriteReg8(motors_i2c, LED0_ON_H + LED_MULTIPLYER * (led - 1), on_value >> 8);

	wiringPiI2CWriteReg8(motors_i2c, LED0_OFF_L + LED_MULTIPLYER * (led - 1), off_value & 0xFF);

	wiringPiI2CWriteReg8(motors_i2c, LED0_OFF_H + LED_MULTIPLYER * (led - 1), off_value >> 8);
	#endif

}

//! PWM a single channel
/*!
 \param led channel (1-16) to set PWM value for
 \param value 0-4095 value for PWM
 */
void setPWM(uint8_t led, int value) {
	setPWM2(led, 0, value);
}


//! Get current PWM value
/*!
 \param led channel (1-16) to get PWM value from
 */
int getPWM(uint8_t led) {
	int ledval = 0;
	#ifndef _WIN32
	ledval = wiringPiI2CReadReg8(motors_i2c, LED0_OFF_H + LED_MULTIPLYER * (led-1));
	ledval = ledval & 0xf;
	ledval <<= 8;
	ledval += wiringPiI2CReadReg8(motors_i2c, LED0_OFF_L + LED_MULTIPLYER * (led-1));
	#endif
	return ledval;
}


drivers_response_T motorDrvInit(void) {
    // I2C addresses for PWM board and IMU
	int pwm_address=0x40;
	bool init_error = false;

    /******** configure I2C driver *******/
	// Setup I2C communication for PWM board
	motors_i2c = wiringPiI2CSetup(pwm_address);
	if (motors_i2c < 0) {
    	SystemLog("PWM board config error");
		init_error = true;
    
  	} else {
		SystemLog("PWM board configured");
	}
    setPWMFreq(60);
	//setPWMFreq(300);

	/*******configure outputs for wheels ****/
	SystemLog("configuring wheel outputs");
	pinMode(LEFT_MOTOR_PIN1, OUTPUT);
	pinMode(LEFT_MOTOR_PIN2, OUTPUT);
	//pinMode(RIGHT_MOTOR_PIN1, OUTPUT);
	//pinMode(RIGHT_MOTOR_PIN2, OUTPUT);

	//setRightMotorThrottle(0);
	setLeftMotorThrottle(0);

	if (init_error == false) {
		return driver_ok;
	}
	else {
		return driver_init_error;
	}
}


// Sets forward direction
void setLeftMotorForward(void) {

#ifndef _WIN32	
	digitalWrite(LEFT_MOTOR_PIN1, LOW);
	digitalWrite(LEFT_MOTOR_PIN2, HIGH);
#endif

}

// Sets forward direction
void setRightMotorForward(void) {

#ifndef _WIN32	
	digitalWrite(RIGHT_MOTOR_PIN1, LOW);
	digitalWrite(RIGHT_MOTOR_PIN2, HIGH);
#endif

}

// Sets backward direction
void setRightMotorBackward(void) {

#ifndef _WIN32	
	digitalWrite(RIGHT_MOTOR_PIN1, HIGH);
	digitalWrite(RIGHT_MOTOR_PIN2, LOW);
#endif

}

// Sets backward direction
void setLeftMotorBackward(void) {

#ifndef _WIN32	
	digitalWrite(LEFT_MOTOR_PIN1, HIGH);
	digitalWrite(LEFT_MOTOR_PIN2, LOW);
#endif

}

void setRightMotorThrottle(uint8_t value) {
	setPWM(RIGHT_MOTOR_PWM,value);
}

void setLeftMotorThrottle(uint8_t value) {
	setPWM(LEFT_MOTOR_PWM,value);
}
