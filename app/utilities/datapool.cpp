#include "datapool.hpp"

//variable defintion
static allow_transition_T allow_transition_dpool;
static emergency_break_T ebreak_dpool;
static velocity_T ego_velocity_dpool;
static distance_T ego_distance_dpool;

static distance_T fr_usonic_distance_dpool;
static distance_T fc_usonic_distance_dpool;
static distance_T fl_usonic_distance_dpool;
sensor_status_T fr_usonic_status_dpool;
sensor_status_T fc_usonic_status_dpool;
sensor_status_T fl_usonic_status_dpool;

steer_T steering_dpool;
throttle_T right_motor_throttle_dpool;
throttle_T left_motor_throttle_dpool;
gear_T gear_dpool;


ecoderCounter_T encoder_counter1_dpool;
ecoderCounter_T encoder_counter2_dpool;

system_status_T system_status_dpool;
system_status_T ecu_status_dpool;

velocity_T velocity_dpool;

void DataPoolInit(void) {

}

emergency_break_T DataPoolReadEBreak(void) {
  return ebreak_dpool;
}
void DataPoolWriteEBreak(emergency_break_T ebreak_local) {
  ebreak_dpool = ebreak_local;
}


steer_T DataPoolReadSteering(void) {
  return steering_dpool;
}
void DataPoolWriteSteering(steer_T steering_local) {
  steering_dpool = steering_local;
}

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



gear_T DataPoolReadGear(void) {
  return gear_dpool;
}

void DataPoolWriteGear(gear_T gear_local) {
  gear_dpool = gear_local;
}


velocity_T DataPoolReadVelocityCmd(void) {
  return velocity_dpool;
}

void DataPoolWriteVelocityCmd(velocity_T velocity_cmd_local) {
  velocity_dpool = velocity_cmd_local;
}


//Perception

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


distance_T DataPoolReadFrUltrasonicsDistance(void) {
  return fr_usonic_distance_dpool;
}

void DataPoolWriteFrUltrasonicsDistance(distance_T fr_usonic_distance_local) {
  fr_usonic_distance_dpool = fr_usonic_distance_local;
}

distance_T DataPoolReadFlUltrasonicsDistance(void) {
  return fl_usonic_distance_dpool;
}

void DataPoolWriteFlUltrasonicsDistance(distance_T fl_usonic_distance_local) {
  fl_usonic_distance_dpool = fl_usonic_distance_local;
}

distance_T DataPoolReadFcUltrasonicsDistance(void) {
  return fc_usonic_distance_dpool;
}

void DataPoolWriteFcUltrasonicsDistance(distance_T fc_usonic_distance_local) {
  fc_usonic_distance_dpool = fc_usonic_distance_local;
}

sensor_status_T DataPoolReadFrUltrasonicsStatus(void) {
  return fr_usonic_status_dpool;
}

void DataPoolWriteFrUltrasonicsStatus(sensor_status_T fr_usonic_status_local) {
  fr_usonic_status_dpool = fr_usonic_status_local;
}

sensor_status_T DataPoolReadFlUltrasonicsStatus(void) {
  return fl_usonic_status_dpool;
}

void DataPoolWriteFlUltrasonicsStatus(sensor_status_T fl_usonic_status_local) {
  fl_usonic_status_dpool = fl_usonic_status_local;
}

sensor_status_T DataPoolReadFcUltrasonicsStatus(void) {
  return fc_usonic_status_dpool;
}

void DataPoolWriteFcUltrasonicsStatus(sensor_status_T fc_usonic_status_local) {
  fc_usonic_status_dpool = fc_usonic_status_local;
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
void DataPoolWriteEncoderCounter2(ecoderCounter_T encoder_counter2_dpool) {
  encoder_counter2_dpool = encoder_counter2_dpool;
}


// Safety Monitor

system_status_T DataPoolReadSystemStatus(void) {
  return system_status_dpool;
}

void DataPoolWriteSystemStatus(system_status_T system_status_local) {
  system_status_dpool = system_status_local;
}

system_status_T DataPoolReadEcuStatus(void) {
  return ecu_status_dpool;
}

void DataPoolWriteEcuStatus(system_status_T ecu_status_local) {
  ecu_status_dpool = ecu_status_local;
}