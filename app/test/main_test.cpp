#include "test_cfg.hpp"
#include "logger_test.hpp"

static void readInputs(void) {

}

static void writeOutputs(void) {
    
}

void mainTest(void) {

    readInputs();

    #ifdef LOGGER_TEST
    loggerTestStep();
    #endif
	
    writeOutputs();

}