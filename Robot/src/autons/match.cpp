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
    pidDrive(-17, 0, 3000, 0.1);
    delay(10);
    setIntake(-600);
    pidTurnToPoint({60, -290}, 2.4, 2, 0, true);
    pidDrive(-20, gyro2.get_heading(), 3000, 0.1);
    delay(10);
    shootCata();
    pidTurn(-60, 2.41, 2, 0);
    pp::runpp(path, true, 5000, 25);
    setIntake(0);
    pidDrive(5, -45, 3000, 0.1);
    delay(10);
    pidTurn(-90, 2.41, 2, 0);
    driveUntilRoller();
    chassis->forward(0.005);
    roll(team);
    chassis->stop();
}
