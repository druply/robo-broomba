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

static void writeOutputs(void) {
    	std::cout << "right motor: " <<  DataPoolReadRightMotorThrottle() << std::endl;
	std::cout << "left motor: " <<  DataPoolReadLeftMotorThrottle() << std::endl;

}

void loggerTestStep(void) {

    readInputs();

    writeOutputs();

}
