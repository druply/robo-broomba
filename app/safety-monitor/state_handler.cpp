
#include "datatypes.hpp"
#include "state_handler.hpp"
#include "datapool.hpp"
#include "sys_logger.hpp"
#include "motion_monitor.hpp"

/*
state array
*/
std::vector<system_states_T> states = {
    {SystemState::init, SystemEvent::init_pass, SystemState::test_init},
    {SystemState::test_init, SystemEvent::test_init_pass, SystemState::run},
    {SystemState::test_init, SystemEvent::test_init_fail, SystemState::diag}
};


SystemState system_state;
SystemEvent system_event;

void stateHandlerInit(void) {
    system_state = SystemState::init; // initialize system
    DataPoolWriteSystemStatus(system_state); // write status to datapool
}

/*
Transition to next state
*/
static void switchTransition(void) {

    std::vector<system_states_T>::iterator itr;

    for (itr = states.begin(); itr != states.end(); itr++) {
        if ((itr->current_state == system_state) && (itr->system_event == system_event)) {
            system_state = itr->next_state;
            break;
        }
    }
}


/*
Main function for state handler
*/
void stateHandlerStep(void) {

    switchTransition();

    DataPoolWriteSystemStatus(system_state); // write status to datapool

    switch(system_state) {

        case SystemState::init:
            // do stuf at init
            system_event = SystemEvent::init_pass;
            SystemLog("state handler init");

            break;

        case SystemState::test_init:
            
            system_event = testInitStep();
            //system_event = SystemEvent::test_init_pass; // test init has passed
            SystemLog("state handler test init");
            break;

        case SystemState::run:
            SystemLog("state handler run");    
            break;

        case SystemState::deinit:
            break;

        default:
            break;
    }

}