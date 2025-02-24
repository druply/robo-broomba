#include "motion_monitor.hpp"
#include "motion_control.hpp"
#include <vector>


/*
state array
*/
std::vector<test_init_states_T> init_states = {
    {testInitStates::stop, testInitEvents::move_forward, testInitStates::forward}
};


testInitStates curr_state;
testInitEvents local_event;
motion_control_T motion_cmd;

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

static SystemEvent moveForward(void) {
    
    SystemEvent event_res;
    motion_cmd.action = action_E::move;
    motion_cmd.gear = gear_E::forward;
    motion_cmd.velocity = 0.2;
    motion_cmd.angle = 0;
    event_res = SystemEvent::wait;



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

    switch(curr_state) {

        case testInitStates::stop:
            system_event_res = SystemEvent::wait;
            motion_cmd.action = action_E::stop;
            motion_cmd.gear = gear_E::forward;
            motion_cmd.velocity = 0.0;
            motion_cmd.angle = 0.0;

            ctr++;
            if (ctr == 50) {
                local_event = testInitEvents::move_forward;
            }
            break;

        case testInitStates::forward:
            system_event_res = moveForward();
            
            break;

        case testInitStates::backward:
        system_event_res = SystemEvent::wait;
        break;

        case testInitStates::right:
        system_event_res = SystemEvent::wait;
        break;

        case testInitStates::left:
        system_event_res = SystemEvent::wait;
        break;

        case testInitStates::done:
        system_event_res = SystemEvent::test_init_pass;
        break;

        default:
        break;

    };

    setMotionControlCmd(motion_cmd); // pass motion control cmd


    return system_event_res;
}
