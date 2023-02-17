#pragma once
#include "main.h"

extern void catapult();
extern void shootCata();
extern void intakeControl();
extern void setIntake(int vel);
extern void shootExpansion();
extern void enableBoost(bool enable);
extern void enableBoostOp();
extern pros::ADIDigitalOut endgame;

#define ENDGAME_DEFAULT false