#ifndef _MOTION_CONTROL_HPP_
#define _MOTION_CONTROL_HPP_

#include "datatypes.hpp"



void setMotionControlCmd(motion_control_T cmd);
void motionControlStep(void);
void motionControlInit(void);

#endif //_MOTION_CONTROL_HPP_