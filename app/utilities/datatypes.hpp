#ifndef DATATYPES_HPP_INCLUDED
#define DATATYPES_HPP_INCLUDED

#include "system_types.hpp"

typedef double distance_T;
typedef double velocity_T;
typedef double angular_velocity_T;
typedef double time_T;

enum class sensor_status_E {
    busy = 0,
    ready,
    skipped,
    error,
    offline
};

enum class device_status_E {
    init,
    app_init,
    ready,
    error
};

enum class SystemEvent {
    init_pass,
    test_init_pass,
    test_init_fail,
    run_fail,
    stop,
    wait
};

enum class SystemState {
	init,
    test_init,
	run,
    diag,
    deinit
};

typedef struct system_states_T {
    SystemState current_state;
    SystemEvent system_event;
    SystemState next_state;
};


typedef double angle_T;
typedef double reliability_T;
typedef int lenght_of_data_T;

////*** IMU datatypes ***/////
//axis data type
typedef double axis_T;
typedef double die_temperature_T;

//imu data structure
typedef struct {
    axis_T acc_x;
    axis_T acc_y;
    axis_T acc_z;
    axis_T mag_x;
    axis_T mag_y;
    axis_T mag_z;
    axis_T gyr_x;
    axis_T gyr_y;
    axis_T gyr_z;
    die_temperature_T  temperature;
    sensor_status_E status;
} imu_T;


///*** Lidar types ****/////
#define     CX_LIDAR_BUSY           0
#define     CX_LIDAR_READY          1
#define     CX_LIDAR_SKIPPED        2
#define     CX_LIDAR_ERROR          3
#define     CX_LIDAR_OFFLINE        4

#define     CX_MAX_LIDAR_POINTS      500

#define		PI_DIV_4	(M_PI/4)
#define		PI_DIV_2	(M_PI/2)
#define		PI_DIV_34	((3*M_PI)/4)	
	
#define		PI_DIV_24	(M_PI/24)	


struct  lidar_scan_S {
    distance_T distance;
    angle_T angle;
    reliability_T reliability;
};


typedef struct {
    struct lidar_scan_S lidar_scan[CX_MAX_LIDAR_POINTS];
    distance_T front_center;
    distance_T front_right;
    distance_T right;
    distance_T rear_right;
    distance_T rear_center;
    distance_T rear_left;
    distance_T left;
    distance_T front_left;
    distance_T nearest_object;
    lenght_of_data_T length;
    sensor_status_E status;
} lidar_T;



////**Ultrasonics ***/////
typedef enum  {
    sensor1 = 0,
    sensor2,
    sensor3,
    sensor4,
    sensor5,
    sensor6
} ultrasonic_T;


typedef struct {
    distance_T distance;
    sensor_status_E status;
} usonic_data_T;

////**** GPIO //////
typedef int  cxpin_T;
typedef  int bLevel_T;
typedef volatile uint32 ecoderCounter_T;

typedef enum {
    right = 0,
    left
} encoder_T;


/// Actuator types//////
typedef int steer_T;
typedef double throttle_T;

enum class gear_E {
    forward = 0,
    reverse
} ;

typedef int pan_T;

// camera resolution
#define X_PIXELS    680
#define Y_PIXELS    480

typedef struct {
    int depth[X_PIXELS][Y_PIXELS];
    int R[X_PIXELS][Y_PIXELS];
    int G[X_PIXELS][Y_PIXELS];
    int B[X_PIXELS][Y_PIXELS];
    int status;
} camera_T;


typedef enum {
    sys_stopped=0,
    sys_initiliazing,
    sys_ready,
    sys_runinng,
    sys_error
} system_status_T;

typedef enum {
    invalid = 0,
    ok
} response_T;

typedef enum {
    e_break_off = 0,
    e_break_on
} emergency_break_T;

// typedef enum {
//      forward = 0,
//      forward_right,
//      forward_left,
//      stop,
//      reverse,
//      reverse_right,
//      reverse_left
//  } maneuver_T;

typedef volatile int maneuver_T;
typedef int counter_T;
typedef int allow_transition_T;


/*
Motion control datatypes
*/
enum class action_E {
    move,
    rotate_right,
    rotate_left,
    stop
};

typedef struct motion_control_T {
    action_E action;
    gear_E gear;
    velocity_T velocity;
    angle_T angle;
};



#endif // STANDARD_TYPES_HPP_INCLUDED
