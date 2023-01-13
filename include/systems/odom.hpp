#pragma once
#include "main.h"

#define LEFT_ENCODER_TOP 'A'
#define LEFT_ENCODER_BOTTOM 'B'

#define RIGHT_ENCODER_TOP 'C'
#define RIGHT_ENCODER_BOTTOM 'D'

#define SIDE_ENCODER_TOP 'E'
#define SIDE_ENCODER_BOTTOM 'F'

#define ODOM_WHEEL_DIAMETER_CM 7.06882 //cm

#define DEGREES_TO_CM (ODOM_WHEEL_DIAMETER_CM * pi / 360)

namespace odom{
    static float d1 = 18.75; //left to center, cm
    static float d2 = 18.75; //right to center, cm
    static float d3 = 17; //back to center, cm

    double x, y, theta;
    double leftL, rightL, sideL, gyroL;

    void updatePos(float left, float right, float side, float gyro);
    void printPos();
    void resetEncoders();
    void printEncoders();
}

void runOdomTracking();