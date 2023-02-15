#include "main.h"
using pros::delay;
/*
@param team true if blue, false if red
*/
void carry(bool team)
{
    enableBoost(true);
    driveUntilRoller();
    chassis->forward(0.005);
    roll(team);
    chassis->stop();
    pidDrive(-17, 0, 4000, 0.1);
    delay(10);
    setIntake(-600);
    pidTurnToPoint({60, -290}, 2.4, 2, 0, true);
    pidDrive(-20, gyro2.get_heading(), 4000, 0.1);
    delay(10);
    shootCata();
    pidTurn(-60, 2.41, 2, 0);
    pp::runpp(path, true, 5000, 25);
    setIntake(0);
    delay(10);
    pidTurn(-90, 2.41, 2, 0);
    driveUntilRoller();
    chassis->forward(0.005);
    roll(team);
    chassis->stop();
}

void teamL(bool team)
{
    enableBoost(true);
    driveUntilRoller();
    chassis->forward(0.005);
    roll(team);
    chassis->stop();
    pidDrive(-17, 0, 4000, 0.1);
    delay(10);
    setIntake(-600);
    pidTurnToPoint({60, -290}, 2.4, 2, 0, true);
    pidDrive(-20, gyro2.get_heading(), 4000, 0.1);
    delay(10);
    shootCata();
    pidTurn(-120, 2.41, 2, 0);
    setIntake(100);
    pidDrive(50, -120, 9000, 0.1);
    delay(200);
    setIntake(-600);
    pidDrive(55, -120, 5000, 0.1);
    delay(10);
    pidTurnToPoint({50, -270}, 2.4, 2, 0, true);
    pidDrive(-35, gyro2.get_heading(), 3000, 0.1);
    setIntake(0);
    shootCata();
}

void teamR(bool team)
{
    enableBoost(true);
    pidDrive(-7, 0, 6000, 0.1);
    delay(10);
    pidTurnToPoint({-110, -310}, 2.4, 2, 0, true);
    pidDrive(-50, gyro2.get_heading(), 6000, 0.1);
    delay(10);
    shootCata();
    pidDrive(7, 0, 6000, 0.3);
    delay(10);
    setIntake(-600);
    pidTurn(125, 2.41, 2, 0);
    pidDrive(100, 135, 5000, 0.1);
    pidTurnToPoint({-110, -300}, 2.4, 2, 0, true);
    pidDrive(-30, gyro2.get_heading(), 6000, 0.1);
    delay(10);
    shootCata();
}