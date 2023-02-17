#include "main.h"
using pros::delay;
void skills()
{
    enableBoost(false);
    //roller1
    driveUntilRoller();
    chassis->forward(0.002);
    roll(false);
    chassis->stop();
    pidDrive(-35, 0, 6000, 0.1); 
    delay(10);
    pidTurn(90, 2.44, 2.5, 0);
    delay(10);
    setIntake(-600);
    pidDrive(45, 90, 4000);
    delay(10);
    setIntake(0);
    pidDrive(15, 90, 5000);
    delay(10);

    //roller2
    driveUntilRoller();
    chassis->forward(0.002);
    roll(false);
    chassis->stop();
    pidDrive(-30, 90, 5000, 0.1); 
    delay(10);
    pidTurn(0, 2.5, 2, 0);
    setIntake(-600);

    //to goal
    pp::runpp(path_s_1, false, 6000, 40);
    delay(10);
    setIntake(0);
    pidTurnToPoint({50, -230}, 2.4, 2, 0, true);
    shootCata();

    delay(300);

    //low goal disks
    pidTurn(-175, 2.41, 2, 0);
    setIntake(-600);
    pidDrive(100, -90, 2000, 0.06);
    delay(10);
    pp::runpp(path_s_2, false, 6000, 40);
    delay(10);
    pidTurnToPoint({45, -230}, 2.4, 2, 0, true);

    setIntake(0);
    shootCata();
    delay(300);

    //middle disks

    setIntake(-600);
    pp::runpp(path_s_3, true, 6000, 25);
    delay(100);
    pidTurnToPoint({-100, -210}, 2.4, 2, 0, false);
    pp::runpp(path_s_4, true, 4000, 25);
    delay(10);
    pidTurnToPoint({60, -285}, 2.4, 2, 0, true);
    pidDrive(-15, gyro2.get_heading(), 4000, 0.11);
    delay(10);

    setIntake(0);
    shootCata();

    delay(300);

    //knocking 3 stack

    pidTurnToPoint({-120, -245}, 2.4, 2, 0, false);
    double saveAngle1 = gyro2.get_heading();
    // pidTurn(-139, 2.4, 2, 0);
    pidDrive(90, saveAngle1, 8000, 0.13);
    setIntake(-600);
    delay(100);
    pidDrive(80, saveAngle1, 2000, 0.11);
    delay(10);
    pidTurnToPoint({50, -280}, 2.4, 2, 0, true);
    pp::runpp(path_s_6, false, 5000, 30);
    pidTurnToPoint({50, -270}, 2.4, 2, 0, false);
    setIntake(0);
    shootCata();

    //roller 3
    pidTurn(-80, 2.4, 2, 0);
    setIntake(-600);
    pidDrive(70, gyro2.get_heading(), 9000, 0.11);
    delay(10);
    pidDrive(15, gyro2.get_heading(), 4000, 0.11);
    delay(10);
    pidTurn(-90, 2.4, 2, 0);
    pidDrive(80, -90, 3000, 0.11);
    delay(10);
    pidDrive(-10, -90, 5000, 0.11);
    delay(10);
    setIntake(0);
    driveUntilRoller();
    chassis->forward(0.002);
    roll(false);
    chassis->stop();
    pidDrive(-75, -90, 5000, 0.1); 
    delay(10);
    setIntake(-600);
    pidTurn(180, 2.4, 2, 0);
    pidDrive(30, 180, 3000, 0.11);
    delay(10);
    pidDrive(-10, 180, 3000, 0.11);
    delay(10);
    setIntake(0);
    //roller 4
    driveUntilRoller();
    chassis->forward(0.002);
    roll(false);
    chassis->stop();

    pidDrive(-40, 180, 3000, 0.11);
    delay(10);
    pidTurn(-135, 2.4, 2, 0);

    endgame.set_value(!ENDGAME_DEFAULT);


}

void skills1()
{
    driveUntilRoller();
    chassis->forward(0.002);
    roll(false);
    chassis->stop();
    pidDrive(-35, 0, 3000, 0.1); 
    delay(10);
    std::cout << "boo" << std::endl;
    pidTurn(90, 2.44, 2.5, 0);
    delay(10);
    setIntake(-600);
    pidDrive(45, 90, 5000);
    delay(10);
    setIntake(0);
    pidDrive(15, 90, 5000);
    delay(10);
    driveUntilRoller();
    chassis->forward(0.002);
    roll(false);
    chassis->stop();
    pidDrive(-30, 90, 5000, 0.1); 
    delay(10);
    pidTurn(0, 2.5, 2, 0);
    setIntake(-600);
    pp::runpp(path_s_1, false, 6000, 40);
    delay(10);
    setIntake(0);
    pidTurnToPoint({52, -230}, 2.4, 2, 0, true);
    shootCata();
    setIntake(-600);
    pp::runpp(path_s_3, true, 3000, 25);
    delay(10);
    pidTurnToPoint({-100, -210}, 2.3, 2, 0, false);
    pp::runpp(path_s_4, true, 3000, 25);
    delay(10);
    pidTurnToPoint({60, -270}, 2.4, 2, 0, true);
    pidDrive(-15, gyro2.get_heading(), 2500, 0.11);
    delay(10);
    // pp::runpp(path_s_1_2, true, 4000, 30);
    // pidTurnToPoint({60, -270}, 2.4, 2, 0, true);
    // setIntake(0);
    // pidDrive(-10, gyro2.get_heading(), 2500, 0.11);
    // delay(10);
    shootCata();
    setIntake(-600);
    pp::runpp(path_s_1_3, true, 5000, 30);
    setIntake(0);
    pidTurn(0, 2.44, 2.5, 0);
    delay(400);
    pidDrive(-30, 0, 2500, 0.11);
    delay(10);
    setIntake(600);
    pidDrive(35, 0, 2500, 0.11);
    delay(10);
    setIntake(0);
    delay(300);
    pidDrive(-30, 0, 2500, 0.11);
    delay(10);
    setIntake(600);
    pidDrive(35, 0, 2500, 0.11);
    delay(10);
    pidTurn(90, 2.44, 2.5, 0);
    pp::runpp(path_s_1_4, false, 6000, 25);
    pidTurnToPoint({-210, -15}, 2.4, 2, 0, true);
    shootCata();
    pp::runpp(path_s_1_5, true, 3000, 25);
    pp::runpp(path_s_1_4, false, 6000, 25);
    pidTurnToPoint({-210, -15}, 2.4, 2, 0, true);
    shootCata();
}