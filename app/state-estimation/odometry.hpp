
#define WHEEL_DIAMETER  (distance_T)0.065 //meters
#define NUMBER_OF_TICKS ((distance_T)30.0) // total number of ticks in 1 revolution
#define WHEEL_TO_WHEEL_DISTANCE  (distance_T)0.14

void odometryInit(void);
void odometryStep(void);
void odometryDeInit(void);