#pragma once
#include "main.h"

#define LEFT_ENCODER_TOP 'A'
#define LEFT_ENCODER_BOTTOM 'B'

#define RIGHT_ENCODER_TOP 'G'
#define RIGHT_ENCODER_BOTTOM 'H'

#define SIDE_ENCODER_TOP 'G'
#define SIDE_ENCODER_BOTTOM 'H'

#define ODOM_WHEEL_DIAMETER_CM 7.06882  // cm

#define DEGREES_TO_CM (ODOM_WHEEL_DIAMETER_CM * pi / 360)

namespace odom {
void updatePosPilons(float left, float right, float side, float gyro);
void updatePos(float left, float right, float side, float gyro);
void printPos();
void resetEncoders();
void printEncoders();
}  // namespace odom

extern void runOdomTracking();