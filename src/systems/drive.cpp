#include "main.h"

Controller controller;

MotorGroup Ldrive({-14,-16,17});
MotorGroup Rdrive({11,12,-13});


std::shared_ptr<okapi::ChassisController> chassisController = ChassisControllerBuilder()
    .withMotors(Ldrive,Rdrive)
    .withDimensions(AbstractMotor::gearset::blue, {{6_in, 12_in}, imev5BlueTPR*(3/5)})
    .build();

std::shared_ptr<okapi::ChassisModel> chassis = chassisController->getModel();

void opDrive(){
    float leftY = controller.getAnalog(ControllerAnalog::leftY);
    float rightX = controller.getAnalog(ControllerAnalog::rightX);
    chassis->arcade(leftY,rightX); //reverse rightY cause weird reversal stuff, easy fix
}

