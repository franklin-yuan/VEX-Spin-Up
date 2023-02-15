#include "main.h"
#define LIMIT_SWITCH 'A'
#define CATA_PORT 18
#define INTAKE_PORT 10

Motor cata(CATA_PORT, false, AbstractMotor::gearset::red, AbstractMotor::encoderUnits::counts);
Motor intake(INTAKE_PORT, false, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::counts);
pros::ADIDigitalIn limitSwitch(LIMIT_SWITCH);
pros::ADIDigitalOut endgame('E', false);
pros::ADIDigitalOut boost('C', true);
ControllerButton launch(ControllerDigital::right);
ControllerButton intakeRun(ControllerDigital::R1);
ControllerButton intakeRunBackwards(ControllerDigital::R2);
ControllerButton expand1(ControllerDigital::A);
ControllerButton expand2(ControllerDigital::X);
ControllerButton boostButton(ControllerDigital::B);

bool toggle1 = false;
bool latch1 = false;

void catapult() {
    while (true) {
        // If limit switch not pressed move down
        if (!limitSwitch.get_value()) {
            cata.moveVelocity(80);
        }
        else {
            pros::Task::delay(50);
            if (launch.changedToReleased()) {
                while (limitSwitch.get_value()) {
                    cata.moveVelocity(30);
                }
                pros::delay(400);
                cata.moveVelocity(0);
            }
            cata.moveVelocity(0);
        }
        pros::Task::delay(20);
    }
}

void shootCata()
{
    while (limitSwitch.get_value()) {
        cata.moveVelocity(30);
    }
    pros::delay(100);
    cata.moveVelocity(0);
    
}

void intakeControl() {
    if (intakeRun.isPressed()) {
        intake.moveVelocity(-600);
    }
    else if (intakeRunBackwards.isPressed()) {
        intake.moveVelocity(400);
    }
    else{
        intake.moveVelocity(0);
    }
}

void setIntake(int vel) {
    intake.moveVelocity(vel);
}

void shootExpansion() {
    if (expand1.isPressed() && expand2.isPressed())
    {
        endgame.set_value(true);
        pros::delay(500);
        endgame.set_value(false);
    }
}

void enableBoost(bool enable) {
    boost.set_value(enable);
}

void enableBoostOp() {
    if(boostButton.isPressed()){
        if(!latch1){
            toggle1=!toggle1;
            latch1=true;
        }
    }
    else{
        latch1=false;
    }
    if(toggle1){
        boost.set_value(false);
    }
    else{
        boost.set_value(true);
    }
}
