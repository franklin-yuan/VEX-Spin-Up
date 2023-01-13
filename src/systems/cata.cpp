#include "main.h"
#define LIMIT_SWITCH 'A'
#define CATA_PORT 1


Motor cata(CATA_PORT, false, AbstractMotor::gearset::red, AbstractMotor::encoderUnits::counts);
pros::ADIDigitalIn limitSwitch (LIMIT_SWITCH);
void releaseCata(){
    if(controller.getDigital(ControllerDigital::A)){
        cata.moveVelocity(50);
    }
    else{
        cata.moveVelocity(0);
    }
}

void resetCataFn(){
    cata.moveVelocity(50);
    if(limitSwitch.get_value()){
        releaseCata();
    }
    pros::delay(40);
}
