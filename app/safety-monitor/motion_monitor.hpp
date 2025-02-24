#include "datatypes.hpp"

// Test init data types

enum class testInitEvents {
    move_forward,
    move_backward,
    rotate_right,
    rotate_left,
    finish,
    failed,
    null
};


enum class testInitStates {
    stop,
    forward,
    backward,
    right,
    left,
    done
};

typedef struct test_init_states_T {
    testInitStates curr_state;
    testInitEvents event;
    testInitStates next_state;
};

void testInit(void);
SystemEvent testInitStep(void);