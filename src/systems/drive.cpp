#include "main.h"

Controller controller;

MotorGroup Ldrive({1,2,3});
MotorGroup Rdrive({4,5,6});


std::shared_ptr<okapi::ChassisController> chassisController = ChassisControllerBuilder()
    .withMotors(Ldrive,Rdrive)
    .withDimensions(AbstractMotor::gearset::blue, {{6_in, 12_in}, imev5BlueTPR*(3/5)})
    .build();

std::shared_ptr<okapi::ChassisModel> chassis = chassisController->getModel();

void opDrive(){
    float leftY = controller.getAnalog(ControllerAnalog::leftY);
    float rightX = controller.getAnalog(ControllerAnalog::rightX);
    chassis->arcade(leftY,rightX);
}

