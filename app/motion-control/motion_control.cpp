#include "motion_control.hpp"
#include "datapool.hpp"

void motionControlInit(void) {

    // initialize motion control inputs and outputs
    DataPoolWriteRightMotorThrottle(static_cast<throttle_T>(0.0));
    DataPoolWriteLeftMotorThrottle(static_cast<throttle_T>(0.0));

    DataPoolWriteVelocityCmd(static_cast<velocity_T>(0.0));
    DataPoolWriteSteeringAngle(static_cast<angle_T>(0.0));

}


void setGear(void) {

}


void setVelocity(void) {

}

void setSteeringAngle(void) {

}

static void rotateRobot(action_E action, angle_T angle) {
    if (action == action_E::rotate_left) {
        
    }
}


void motionControlStep(void) {
    SystemState sys_state_local;
    action_E action_local;
    angle_T angle_local;

    sys_state_local = DataPoolReadSystemStatus(); // get current system state
    action_local = DataPoolReadMotionActionCmd(); // get current motion action command
    angle_local = DataPoolReadSteeringAngle();

    if ((sys_state_local == SystemState::run) || (sys_state_local == SystemState::test_init)) {
        // do some valid stuff
        switch(action_local) {
            case action_E::stop:
                DataPoolWriteRightMotorThrottle(static_cast<throttle_T>(0.0));
                DataPoolWriteLeftMotorThrottle(static_cast<throttle_T>(0.0));
                break;

            case action_E::rotate_right:
                rotateRobot(action_local, angle_local);
                break;

            default:
                break;
        };

    }
}


void setMotionControlCmd(motion_control_T cmd) {

    DataPoolWriteVelocityCmd(cmd.velocity);
    DataPoolWriteSteeringAngle(cmd.angle);
    DataPoolWriteGear(cmd.gear);
    DataPoolWriteMotionActionCmd(cmd.action);

}