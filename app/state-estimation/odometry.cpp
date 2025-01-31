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

//temporary
double delta_angle;
double delta_x;
double delta_y;

//output variables
double angle;
double x;
double y;


static void calculateDistances(void) {
    // calculate individual wheel distance traveled
    right_wheel_distance = (((distance_T)right_encoder_ctr - (distance_T)right_encoder_ctr_prev)*wheel_circumference)/NUMBER_OF_TICKS;
    left_wheel_distance  = (((distance_T)left_encoder_ctr - (distance_T)left_encoder_ctr_prev)*wheel_circumference)/NUMBER_OF_TICKS;
    // calculate vehicle distance traveled
    ego_distance += (right_wheel_distance + left_wheel_distance)/2;
    // write ego distance to datapool
    DataPoolWriteEgoDistance(ego_distance);

    // debugging purposes, delete **
    std::cout << "right distance: " << right_wheel_distance << std::endl;
    std::cout << "left distance: "  << left_wheel_distance << std::endl;
    std::cout << "ego distance "<< ego_distance << std::endl;

    // calculate temporary values for angle, x and y
    delta_angle = (right_wheel_distance - left_wheel_distance)/(WHEEL_TO_WHEEL_DISTANCE);
    delta_x = ego_distance*cos(angle);
    delta_y = ego_distance*sin(angle);


    // calculate outputs
    x = x + delta_x;
    y = y + delta_y;
    angle = angle + delta_angle;

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