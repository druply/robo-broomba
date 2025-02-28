#include "motion_monitor.hpp"
#include "motion_control.hpp"
#include "datapool.hpp"
#include <vector>


/*
state array
*/
std::vector<test_init_states_T> init_states = {
    {testInitStates::stop, testInitEvents::done, testInitStates::forward},
    {testInitStates::forward, testInitEvents::done, testInitStates::backward}
};


testInitStates curr_state;
testInitEvents local_event;
//motion_control_T motion_cmd;

void testInit(void) {
    curr_state = testInitStates::stop;
    local_event = testInitEvents::null;
}


static void transitionState(void) {
    std::vector<test_init_states_T>::iterator itr;

    for(itr = init_states.begin(); itr!=init_states.end();itr++) {
        if((itr->curr_state == curr_state) && (itr->event == local_event)) {
            curr_state = itr->next_state;
            break;
        }
    }
}

static testInitEvents moveForward(void) {
    
    testInitEvents event_res;
    ecoderCounter_T encoder1;
    ecoderCounter_T encoder2;
    static ecoderCounter_T prev_encoder1;
    static ecoderCounter_T prev_encoder2;
    distance_T distance;
    static int valid_state_ctr = 0;
    static int invalid_state_ctr = 0;

    //motion_cmd.action = action_E::move;
    DataPoolWriteMotionActionCmd(action_E::move);
    //motion_cmd.gear = gear_E::forward;
    DataPoolWriteGearCmd(gear_E::forward);
    //motion_cmd.velocity = 0.2;
    DataPoolWriteVelocityCmd(0.2);
    //motion_cmd.angle = 0;
    DataPoolWriteSteeringAngleCmd(0.0);

    event_res = testInitEvents::null;


    encoder1 = DataPoolReadEncoderCounter1();
    encoder2 = DataPoolReadEncoderCounter2();

    distance = DataPoolReadEgoDistance();


    if ( (prev_encoder1 != encoder1) &&
         (prev_encoder2 != encoder2) &&
        (DataPoolReadRightMotorThrottle() > 0.0) &&
        (DataPoolReadLeftMotorThrottle() > 0.0) )  
    {
        if (distance >= 0.3) {
            event_res = testInitEvents::done;
        }
        invalid_state_ctr = 0;
    }
    else 
    {
        if ( (DataPoolReadRightMotorThrottle() == 0.0) ||
             (DataPoolReadLeftMotorThrottle() == 0.0) ) 
        {
            invalid_state_ctr++;
        }
       
    }

    if (invalid_state_ctr == 50) {
        event_res = testInitEvents::fail;
    }

    return event_res;
}

/*
Main function 
for init test
this test makes sure the sensors and actuators are working
execute every 20ms
*/
SystemEvent testInitStep(void) {

    SystemEvent system_event_res;

    static int ctr = 0;
    transitionState(); // transition to next state

    system_event_res = SystemEvent::wait;

    switch(curr_state) {

        case testInitStates::stop:

            // motion_cmd.action = action_E::stop;
            DataPoolWriteMotionActionCmd(action_E::stop);
            //motion_cmd.gear = gear_E::forward;
            DataPoolWriteGearCmd(gear_E::forward);
            //motion_cmd.velocity = 0.0;
            DataPoolWriteVelocityCmd(0.0);
            //motion_cmd.angle = 0.0;
            DataPoolWriteSteeringAngleCmd(0.0);

            ctr++;
            if (ctr == 50) {
                local_event = testInitEvents::done;
                ctr = 0;
            }
            break;

        case testInitStates::forward:

            local_event = moveForward();

            if (local_event == testInitEvents::fail) {
                system_event_res = SystemEvent::fail;
            }
            
            break;

        case testInitStates::backward:
        system_event_res = SystemEvent::pass; // remove!!
        break;

        case testInitStates::right:

        break;

        case testInitStates::left:

        break;

        case testInitStates::done:
        system_event_res = SystemEvent::pass;
        break;

        default:
        break;

    };

    //setMotionControlCmd(motion_cmd); // pass motion control cmd


    return system_event_res;
}
