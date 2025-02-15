
#include "state-handler.hpp"

SystemState system_state;

void stateHandlerInit(void) {
    system_state = SystemState::Init;
}

void stateHandlerStep(void) {

    switch(system_state) {

        case SystemState::Init:
            break;

        case SystemState::Run:
            break;

        case SystemState::DeInit:
            break;

        default:
            break;
    }

}