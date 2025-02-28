#include "datatypes.hpp"

// Test init data types

enum class testInitEvents {
    fail,
    done,
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