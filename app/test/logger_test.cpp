#include "datatypes.hpp"
#include "system_types.hpp"
#include "datapool.hpp"
#include "odometry.hpp"
#include "sys_mon.hpp"
#include "test_cfg.hpp"

#include <iostream>
#include <iomanip>

static void readInputs(void) { 
    imu_T imu_in;

    std::cout << "encoder 1: " <<  DataPoolReadEncoderCounter1() << std::endl;
	std::cout << "encoder 2: " <<  DataPoolReadEncoderCounter2() << std::endl;
    DataPoolReadImuData(&imu_in);
    
    if (imu_in.status == sensor_status_E::ready) {
        std::cout << std::fixed;
        std::cout << std::setprecision(2);
        std::cout << "acc_x" << imu_in.acc_x << std::endl;
        std::cout << "acc_y" << imu_in.acc_y << std::endl;
        std::cout << "acc_z" << imu_in.acc_z << std::endl;

        std::cout << "gyr_x" << imu_in.gyr_x << std::endl;
        std::cout << "gyr_y" << imu_in.gyr_y << std::endl;
        std::cout << "gyr_z" << imu_in.gyr_z << std::endl;

        std::cout << "temperature" << imu_in.temperature << std::endl;
    }
    else {
        std::cout << "imu not ready" << std::endl;
    }

}

static void writeOutputs(void) {
    	std::cout << "right motor: " <<  DataPoolReadRightMotorThrottle() << std::endl;
	std::cout << "left motor: " <<  DataPoolReadLeftMotorThrottle() << std::endl;

}

void loggerTestStep(void) {

    readInputs();

    writeOutputs();

}
