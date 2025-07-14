#ifndef DATAPOOL_H_
#define DATAPOOL_H_

#include "datatypes.hpp"

/*
* Motor throttle signals
*/
throttle_T DataPoolReadRightMotorThrottle(void);
void DataPoolWriteRightMotorThrottle(throttle_T throttle_local);
throttle_T DataPoolReadLeftMotorThrottle(void);
void DataPoolWriteLeftMotorThrottle(throttle_T throttle_local);

/*
* Encoder signals
*/
ecoderCounter_T DataPoolReadEncoderCounter1(void);
void DataPoolWriteEncoderCounter1(ecoderCounter_T encoder_counter1_local);
ecoderCounter_T DataPoolReadEncoderCounter2(void);
void DataPoolWriteEncoderCounter2(ecoderCounter_T encoder_counter2_dpool);

void DataPoolWriteImuData(imu_T *imu_local);
void DataPoolReadImuData(imu_T *imu_local);

/*
Perception
*/
velocity_T DataPoolReadEgoVelocity(void);
void DataPoolWriteEgoVelocity(velocity_T ego_velocity_local);

distance_T DataPoolReadEgoDistance(void);
void DataPoolWriteEgoDistance(distance_T ego_distance_local);

angle_T DataPoolReadEgoYawAngle(void);
void DataPoolWriteEgoYawAngle(angle_T ego_angle_local);


/*
Motion control
*/
angle_T DataPoolReadSteeringAngleCmd(void);
void DataPoolWriteSteeringAngleCmd(angle_T steering_local);

SystemState DataPoolReadSystemStatus(void);
void DataPoolWriteSystemStatus(SystemState system_status_local);

gear_E DataPoolReadGearCmd(void);
void DataPoolWriteGearCmd(gear_E gear_local);

action_E DataPoolReadMotionActionCmd(void);
void DataPoolWriteMotionActionCmd(action_E cmd_local);

velocity_T DataPoolReadVelocityCmd(void);
void DataPoolWriteVelocityCmd(velocity_T velocity_cmd_local);

emergency_break_T DataPoolReadEBreak(void);
void DataPoolWriteEBreak(emergency_break_T ebreak_local);



system_status_T DataPoolReadEcuStatus(void);
void DataPoolWriteEcuStatus(system_status_T system_status_local);

#endif //DATAPOOL_H_