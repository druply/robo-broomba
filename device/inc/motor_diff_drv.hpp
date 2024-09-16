#ifndef _MOTOR_DRV_INCLUDED_
#define _MOTOR_DRV_INCLUDED_

/*=============================================
		INCLUDES
==============================================*/
#include "device_types.hpp"

/*======================
		DEFINES
=======================*/
// define pins to be used for motors
#define  LEFT_MOTOR_PIN1	    27
#define  LEFT_MOTOR_PIN2	    28
#define  RIGHT_MOTOR_PIN1	    0
#define  RIGHT_MOTOR_PIN2	    2

//define pins to be used for pwm board
#define RIGHT_MOTOR_PWM    1
#define LEFT_MOTOR_PWM     0

// Register Definitions
#define MODE1 				0x00			//Mode  register  1
#define MODE2 				0x01			//Mode  register  2
#define SUBADR1 			0x02			//I2C-bus subaddress 1
#define SUBADR2 			0x03			//I2C-bus subaddress 2
#define SUBADR3 			0x04			//I2C-bus subaddress 3
#define ALLCALLADR 			0x05     		//LED All Call I2C-bus address
#define LED0 				0x6				//LED0 start register
#define LED0_ON_L 			0x6				//LED0 output and brightness control byte 0
#define LED0_ON_H 			0x7				//LED0 output and brightness control byte 1
#define LED0_OFF_L 			0x8				//LED0 output and brightness control byte 2
#define LED0_OFF_H 			0x9				//LED0 output and brightness control byte 3
#define LED_MULTIPLYER 		4				// For the other 15 channels
#define ALLLED_ON_L 		0xFA    		//load all the LEDn_ON registers, byte 0 (turn 0-7 channels on)
#define ALLLED_ON_H 		0xFB			//load all the LEDn_ON registers, byte 1 (turn 8-15 channels on)
#define ALLLED_OFF_L 		0xFC			//load all the LEDn_OFF registers, byte 0 (turn 0-7 channels off)
#define ALLLED_OFF_H 		0xFD			//load all the LEDn_OFF registers, byte 1 (turn 8-15 channels off)
#define PRE_SCALE 			0xFE			//prescaler for output frequency
#define CLOCK_FREQ 			25000000.0 		//25MHz default osc clock

/*======================
		VARIABLES
=======================*/

/*======================
		FUNCTIONS
=======================*/
drivers_response_T motorDrvInit(void);
void setLeftMotorForward(void);
void setRightMotorForward(void);
void setRightMotorBackward(void);
void setLeftMotorBackward(void);
void setRightMotorThrottle(uint8_t value);
void setLeftMotorThrottle(uint8_t value);

#endif // _MOTOR_DRV_INCLUDED_