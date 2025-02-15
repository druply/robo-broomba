#include "datatypes.hpp"
#include "datapool.hpp"
#include "odometry.hpp"
#include <cmath>

#include <iostream>

static distance_T left_wheel_distance;
static distance_T right_wheel_distance;
static distance_T ego_distance;
ecoderCounter_T right_encoder_ctr;
ecoderCounter_T left_encoder_ctr;
ecoderCounter_T right_encoder_ctr_prev;
ecoderCounter_T left_encoder_ctr_prev;
// calculate wheel circumference
const distance_T wheel_circumference = (distance_T)M_PI*(WHEEL_DIAMETER);

const time_T delta_time = 0.1;

//temporary
angle_T delta_angle;
distance_T delta_x;
distance_T delta_y;

//output variables
angle_T angle;
distance_T x;
distance_T y;
angular_velocity_T angle_velocity;
velocity_T x_velocity;
velocity_T y_velocity;
velocity_T ego_velocity;



static void calculateDistances(void) {
    
    velocity_T right_wheel_velocity;
    velocity_T left_wheel_velocity;

    // calculate individual wheel distance traveled
    right_wheel_distance = ( (static_cast<distance_T>(right_encoder_ctr) - static_cast<distance_T>(right_encoder_ctr_prev) ) * wheel_circumference)
                              /NUMBER_OF_TICKS;
    left_wheel_distance  = ( (static_cast<distance_T>(left_encoder_ctr)  - static_cast<distance_T>(left_encoder_ctr_prev)   ) * wheel_circumference)
                              /NUMBER_OF_TICKS;
    
    //calculate right wheel velocity
    right_wheel_velocity = (right_wheel_distance / static_cast<distance_T>(delta_time));
    left_wheel_velocity  = (left_wheel_distance  / static_cast<distance_T>(delta_time));

    // calculate vehicle distance traveled
    ego_distance += (right_wheel_distance + left_wheel_distance)/2;

    ego_velocity = (right_wheel_velocity + left_wheel_velocity)/2;

    // write ego distance to datapool
    DataPoolWriteEgoDistance(ego_distance);
    // write ego velocity to datapool
    DataPoolWriteEgoVelocity(ego_velocity);

    angle_velocity = (right_wheel_velocity - left_wheel_velocity)/delta_time;

    angle = angle_velocity*delta_time + angle;

    DataPoolWriteEgoAngle(angle);

    x_velocity = ego_velocity*cos(angle);
    y_velocity = ego_velocity*sin(angle);

    // calculate outputs
    x = x_velocity*delta_time + x;
    y = y_velocity*delta_time + y;

    // debugging purposes, delete **
    std::cout << "right distance: " << right_wheel_distance << std::endl;
    std::cout << "left distance: "  << left_wheel_distance << std::endl;
    std::cout << "ego distance "<< ego_distance << std::endl;


    std::cout << "x: " << x << std::endl;
    std::cout << "y: " << y << std::endl;
    std::cout << "angle: " << angle << std::endl;

}

/*
Initialize odometry
*/
void odometryInit(void) {
    left_wheel_distance = 0;
    right_wheel_distance = 0;
    right_encoder_ctr_prev = 0;
    left_encoder_ctr_prev = 0;
    ego_distance = 0;

    angle = 0;
    x = 0;
    y = 0;
    angle_velocity = 0;
    x_velocity = 0;
    y_velocity = 0;
    ego_velocity = 0;
}

/*
Execute odometry algorithm
*/
void odometryStep(void) {
    static int ctr_local = 0;
    
    // 100ms
    if(ctr_local%5 == 0) {
        // read encoders
        right_encoder_ctr = DataPoolReadEncoderCounter1();
        left_encoder_ctr = DataPoolReadEncoderCounter2();
        //calculate distance
        calculateDistances();
        // store previous encoder value
        right_encoder_ctr_prev = right_encoder_ctr;
        left_encoder_ctr_prev = left_encoder_ctr;
    }

    if (ctr_local == 500) {
        ctr_local = 0;
    }

    ctr_local++;

}


/*
Initialize odometry
*/
void odometryDeInit(void) {

}