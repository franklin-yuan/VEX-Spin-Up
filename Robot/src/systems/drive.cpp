#include "main.h"

Controller controller;

MotorGroup Ldrive({-14,-16,17});
MotorGroup Rdrive({11,12,-13});


std::shared_ptr<okapi::ChassisController> chassisController = ChassisControllerBuilder()
    .withMotors(Ldrive,Rdrive)
    .withDimensions(AbstractMotor::gearset::blue, {{6_in, 12_in}, imev5BlueTPR*(3/5)})
    .build();

std::shared_ptr<okapi::ChassisModel> chassis = chassisController->getModel();

double expoDrive(double input)
{
    return 0.5 * (input * input * input) + 0.5 * (input);
}

void opDrive(){
    float leftY = controller.getAnalog(ControllerAnalog::leftY);
    float rightX = controller.getAnalog(ControllerAnalog::rightX);
    //std::cout << leftY << " " << rightX << std::endl;
    leftY = expoDrive(leftY);
    chassis->arcade(leftY,rightX); //reverse rightY cause weird reversal stuff, easy fix
}

/*
Drives forwards until colour sensor senses the roller, using open-loop control.
*/
void driveUntilRoller(double fPower){
    int count = 0;
    int dist = 0;

    uint32_t startTime = pros::millis();

    while (count < 3)
    {

        dist = colourSensor.get_proximity();
        chassis->forward(fPower);

        if((pros::millis()-startTime > 5000)){
            chassis->stop();
            break;
        }

        count = dist > 220 ? count + 1 : 0;
        pros::delay(40);
    }

    chassis->stop();
}

