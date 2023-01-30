#pragma once
#include "main.h"

extern void pidTurn(float theta, float kP, float kD, float kI);
extern void pidDrive(float distance, double angle);