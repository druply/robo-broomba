#include "datapool.hpp"

//variable defintion
static emergency_break_T ebreak_dpool;
static velocity_T ego_velocity_dpool;
static distance_T ego_distance_dpool;

static angle_T ego_yaw_angle_dpool;

static angle_T steering_angle_dpool;
throttle_T right_motor_throttle_dpool;
throttle_T left_motor_throttle_dpool;
gear_E gear_dpool;


static ecoderCounter_T encoder_counter1_dpool;
static ecoderCounter_T encoder_counter2_dpool;
imu_T imu_dpool;

SystemState system_status_dpool;
system_status_T ecu_status_dpool;

velocity_T velocity_dpool;

action_E action_cmd_dpool;

/*
* Motor throttle signals
*/
throttle_T DataPoolReadRightMotorThrottle(void) {
  return right_motor_throttle_dpool;
}
void DataPoolWriteRightMotorThrottle(throttle_T throttle_local) {
  right_motor_throttle_dpool = throttle_local;
}

throttle_T DataPoolReadLeftMotorThrottle(void) {
  return left_motor_throttle_dpool;
}
void DataPoolWriteLeftMotorThrottle(throttle_T throttle_local) {
  left_motor_throttle_dpool = throttle_local;
}

/*
* Encoder signals
*/
ecoderCounter_T DataPoolReadEncoderCounter1(void) {
  return encoder_counter1_dpool;
}
void DataPoolWriteEncoderCounter1(ecoderCounter_T encoder_counter1_local) {
  encoder_counter1_dpool = encoder_counter1_local;
}
ecoderCounter_T DataPoolReadEncoderCounter2(void) {
  return encoder_counter2_dpool;
}
void DataPoolWriteEncoderCounter2(ecoderCounter_T encoder_counter2_local) {
  encoder_counter2_dpool = encoder_counter2_local;
}

/*
* Imu Data
*/
void DataPoolWriteImuData(imu_T *imu_local) {
  imu_dpool = *imu_local;
}

void DataPoolReadImuData(imu_T *imu_local) {
  *imu_local = imu_dpool;
}

/*
Perception
*/
velocity_T DataPoolReadEgoVelocity(void) {
  return ego_velocity_dpool;
}

void DataPoolWriteEgoVelocity(velocity_T ego_velocity_local) {
  ego_velocity_dpool = ego_velocity_local;
}

distance_T DataPoolReadEgoDistance(void) {
  return ego_distance_dpool;
}

void DataPoolWriteEgoDistance(distance_T ego_distance_local) {
  ego_distance_dpool = ego_distance_local;
}

angle_T DataPoolReadEgoYawAngle(void) {
  return ego_yaw_angle_dpool;
}

void DataPoolWriteEgoYawAngle(angle_T ego_angle_local) {
  ego_yaw_angle_dpool = ego_angle_local;
}


/*
Motion control
*/

angle_T DataPoolReadSteeringAngleCmd(void) {
  return steering_angle_dpool;
}

void DataPoolWriteSteeringAngleCmd(angle_T ego_angle_local) {
  steering_angle_dpool = ego_angle_local;
}

gear_E DataPoolReadGearCmd(void) {
  return gear_dpool;
}

void DataPoolWriteGearCmd(gear_E gear_local) {
  gear_dpool = gear_local;
}

action_E DataPoolReadMotionActionCmd(void) {
  return action_cmd_dpool;
}
void DataPoolWriteMotionActionCmd(action_E cmd_local) {
  action_cmd_dpool = cmd_local;
}


velocity_T DataPoolReadVelocityCmd(void) {
  return velocity_dpool;
}

void DataPoolWriteVelocityCmd(velocity_T velocity_cmd_local) {
  velocity_dpool = velocity_cmd_local;
}




emergency_break_T DataPoolReadEBreak(void) {
  return ebreak_dpool;
}
void DataPoolWriteEBreak(emergency_break_T ebreak_local) {
  ebreak_dpool = ebreak_local;
}








//Perception


// Safety Monitor

SystemState DataPoolReadSystemStatus(void) {
  return system_status_dpool;
}

void DataPoolWriteSystemStatus(SystemState system_status_local) {
  system_status_dpool = system_status_local;
}




system_status_T DataPoolReadEcuStatus(void) {
  return ecu_status_dpool;
}

void DataPoolWriteEcuStatus(system_status_T ecu_status_local) {
  ecu_status_dpool = ecu_status_local;
}