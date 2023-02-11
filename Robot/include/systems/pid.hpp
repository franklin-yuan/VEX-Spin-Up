#pragma once
#include "main.h"

extern void pidTurn(float theta, float kP, float kD, float kI);
extern void pidTurnToPoint(point target, float kP, float kD, float kI, bool end);
extern void pidDrive(float distance, double angle, double speed, double kp_a = 0.15);