#ifndef DATAPOOL_H_
#define DATAPOOL_H_

#include "datatypes.hpp"

void DataPoolInit(void);
emergency_break_T DataPoolReadEBreak(void);
void DataPoolWriteEBreak(emergency_break_T ebreak_local);

velocity_T DataPoolReadEgoVelocity(void);
void DataPoolWriteEgoVelocity(velocity_T ego_velocity_local);

distance_T DataPoolReadEgoDistance(void);
void DataPoolWriteEgoDistance(distance_T ego_distance_local);

distance_T DataPoolReadFrUltrasonicsDistance(void);
void DataPoolWriteFrUltrasonicsDistance(distance_T fr_usonic_distance_local);

distance_T DataPoolReadFlUltrasonicsDistance(void);
void DataPoolWriteFlUltrasonicsDistance(distance_T fl_usonic_distance_local);

distance_T DataPoolReadFcUltrasonicsDistance(void);
void DataPoolWriteFcUltrasonicsDistance(distance_T fc_usonic_distance_local);

sensor_status_T DataPoolReadFrUltrasonicsStatus(void);
void DataPoolWriteFrUltrasonicsStatus(sensor_status_T fr_usonic_status_local);

sensor_status_T DataPoolReadFlUltrasonicsStatus(void);
void DataPoolWriteFlUltrasonicsStatus(sensor_status_T fl_usonic_status_local);

sensor_status_T DataPoolReadFcUltrasonicsStatus(void);
void DataPoolWriteFcUltrasonicsStatus(sensor_status_T fc_usonic_status_local);

steer_T DataPoolReadSteering(void);
void DataPoolWriteSteering(steer_T steering_local);

throttle_T DataPoolReadRightMotorThrottle(void);
void DataPoolWriteRightMotorThrottle(throttle_T throttle_local);

throttle_T DataPoolReadLeftMotorThrottle(void);
void DataPoolWriteLeftMotorThrottle(throttle_T throttle_local);

gear_T DataPoolReadGear(void);
void DataPoolWriteGear(gear_T gear_local);
ecoderCounter_T DataPoolReadEncoderCounter1(void);
void DataPoolWriteEncoderCounter1(ecoderCounter_T encoder_counter1_local);
ecoderCounter_T DataPoolReadEncoderCounter2(void);
void DataPoolWriteEncoderCounter2(ecoderCounter_T encoder_counter2_dpool);
system_status_T DataPoolReadSystemStatus(void);
void DataPoolWriteSystemStatus(system_status_T system_status_local);
system_status_T DataPoolReadEcuStatus(void);
void DataPoolWriteEcuStatus(system_status_T system_status_local);
velocity_T DataPoolReadVelocityCmd(void);
void DataPoolWriteVelocityCmd(velocity_T velocity_cmd_local);
#endif //DATAPOOL_H_