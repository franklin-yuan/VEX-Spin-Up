#include "main.h"
using pros::delay;
/*
@param team true if blue, false if red
*/
void carry(bool team)
{

    boostEnabled = true;
    enableBoost(true);
    driveUntilRoller();
    chassis->forward(0.002);
    roll(team);
    chassis->stop();
    pidDrive(-14, 0, 4000, 0.1);
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
    chassis->forward(0.002);
    roll(team);
    chassis->stop();

    enableBoost(false);
    boostEnabled = false;
}

void teamL(bool team)
{

    boostEnabled = true;
    enableBoost(true);
    driveUntilRoller();
    roll(team);
    chassis->stop();
    pidDrive(-17, 0, 4000, 0.1);
    delay(10);
    setIntake(0);
    pidTurnToPoint({60, -290}, 2.4, 2, 0, true);
    pidDrive(-20, gyro2.get_heading(), 4000, 0.1);
    delay(10);
    shootCata();
    pidTurn(-120, 2.41, 2, 0);
    setIntake(100);
    pidDrive(50, -120, 9000, 0.1);
    delay(200);
    setIntake(-600);
    pidDrive(55, -120, 3000, 0.1);
    delay(1000);
    pidTurnToPoint({35, -270}, 2.4, 2, 0, true);
    setIntake(0);
    pidDrive(-35, gyro2.get_heading(), 3000, 0.1);
    shootCata();

    enableBoost(false);
    boostEnabled = false;
}

void teamR(bool team)
{
    boostEnabled = true;
    enableBoost(true);
    pidDrive(-7, 0, 6000, 0.1);
    delay(10);
    pidTurnToPoint({-112, -360}, 2.4, 2, 0, true);
    pidDrive(-55, gyro2.get_heading(), 6000, 0.1);
    delay(10);
    shootCata();
    setIntake(0);
    pros::delay(300);
    pidDrive(20, 0, 6000, 0.5);
    delay(200);
    setIntake(-400);
    pidTurn(125, 2.41, 2, 0);
    pidDrive(100, 135, 7000, 0.1);
    delay(1000);
    pidTurnToPoint({-110, -290}, 2.4, 2, 0, true);
    setIntake(600);
    pidDrive(-30, gyro2.get_heading(), 6000, 0.1);
    delay(10);
    shootCata();
    setIntake(0);
    delay(300);
    pidTurn(-44, 2.41, 2, 0);
    pidDrive(160, -44, 6000, 0.1);
    delay(10);
    if (team){
        setIntake(150);
    }
    else{
        setIntake(-150);
    }
    delay(1000);
    setIntake(0);

    enableBoost(false);
    boostEnabled = false;
    // pidTurn(0, 2.41, 2, 0);
    // driveUntilRoller();
    // chassis->forward(0.002);
    // roll(team);
    // chassis->stop();

}