#pragma once
#include "main.h"

extern Controller controller;
extern MotorGroup Ldrive;
extern MotorGroup Rdrive;
extern std::shared_ptr<okapi::ChassisModel> chassis;

extern void opDrive();
extern void driveUntilRoller(double fPower = 0.1);