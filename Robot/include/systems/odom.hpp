#pragma once
#include "main.h"
#include <fstream>
#include <iostream>
#include <string>


#define LEFT_ENCODER_TOP 'A'
#define LEFT_ENCODER_BOTTOM 'B'

#define RIGHT_ENCODER_TOP 'G'
#define RIGHT_ENCODER_BOTTOM 'H'

#define SIDE_ENCODER_TOP 'G'
#define SIDE_ENCODER_BOTTOM 'H'

#define ODOM_WHEEL_DIAMETER_CM 7.06882  // cm
#define DRIVE_WHEEL_DIAMETER_CM 9.1 // cm

#define DEGREES_TO_CM (ODOM_WHEEL_DIAMETER_CM * pi / 360)

#define ADIEXPANDER 20

namespace odom {

void updatePosPilons(float left, float right, float side, float gyro);
void updatePos(float left, float right, float side, float gyro);
void printPos();
void printPosToScreen();
void resetEncoders();
void printEncoders();
void ramseteManual(double xd, double yd, double thetad, double vd, double omegad, float b, float z);
void readFile();

extern double theta, x, y;
}  // namespace odom

extern void runOdomTracking();
extern std::vector<std::vector<double>> path;
extern std::vector<std::vector<double>> path1;
extern std::vector<std::vector<double>> path2;
extern std::vector<std::vector<double>> path3;
extern std::vector<std::vector<double>> path_s_1;
extern std::vector<std::vector<double>> path_s_2;
extern std::vector<std::vector<double>> path_s_3;
extern std::vector<std::vector<double>> path_s_4;
extern std::vector<std::vector<double>> path_s_5;
extern std::vector<std::vector<double>> path_s_6;
extern std::vector<std::vector<double>> path_s_7;
extern std::vector<std::vector<double>> path_s_1_1;
extern std::vector<std::vector<double>> path_s_1_2;
extern std::vector<std::vector<double>> path_s_1_3;
extern std::vector<std::vector<double>> path_s_1_4;
extern std::vector<std::vector<double>> path_s_1_5;
extern std::vector<std::vector<double>> path_s_1_7;
extern std::vector<std::vector<double>> path_s_1_8;
extern pros::ADIEncoder leftEncoder;
extern pros::ADIEncoder rightEncoder;
extern pros::ADIEncoder sideEncoder;