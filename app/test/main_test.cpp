#include "datatypes.hpp"
#include "system_types.hpp"
#include "datapool.hpp"
#include "odometry.hpp"
#include "sys_mon.hpp"
#include "test_cfg.hpp"

#include <iostream>

static void readInputs(void) {
    std::cout << "encoder 1: " <<  DataPoolReadEncoderCounter1() << std::endl;
	std::cout << "encoder 2: " <<  DataPoolReadEncoderCounter2() << std::endl;

}

static void writeInputs(void) {
    
}

void mainTest(void) {

   
    readInputs();
	
    std::cout << "swc step" << std::endl; //  delete **


    odometryStep();

	
    system_exception_T exception_local;

	if (DataPoolReadEgoDistance() > 1.0) {
            exception_local = sys_Halt; // halt system
            SetSystemException(exception_local);
			DataPoolWriteRightMotorThrottle(0);
			DataPoolWriteLeftMotorThrottle(0);
	}

    	
    writeInputs();

	std::cout << "right motor: " <<  DataPoolReadRightMotorThrottle() << std::endl;
	std::cout << "left motor: " <<  DataPoolReadLeftMotorThrottle() << std::endl;

}