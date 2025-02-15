#ifndef STATE_HANDLER_HPP_
#define STATE_HANDLER_HPP_

#include <map>
#include <vector>

enum class SystemEvent {
    pass,
    fail,
    stop
};

enum class SystemState {
	Init,
	Run,
    DeInit
};

typedef struct system_states_T {
    SystemState current_state;
    SystemEvent system_event;
    SystemState next_state;
};

std::vector<system_states_T> states = {
    {SystemState::Init, SystemEvent::pass, SystemState::Run}
};

std::map<SystemState, SystemState> state_transitions = {
	{SystemState::Init, SystemState::Run},
	{SystemState::Run, SystemState::DeInit},
    {SystemState::DeInit, SystemState::Init}
};

void stateHandlerInit(void);
void stateHandlerStep(void);

#endif /* STATE_HANDLER_HPP_ */