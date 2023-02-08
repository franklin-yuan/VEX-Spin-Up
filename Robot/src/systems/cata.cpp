#include "main.h"
#define LIMIT_SWITCH 'A'
#define CATA_PORT 18
#define INTAKE_PORT 10

Motor cata(CATA_PORT, false, AbstractMotor::gearset::red, AbstractMotor::encoderUnits::counts);
Motor intake(INTAKE_PORT, false, AbstractMotor::gearset::blue, AbstractMotor::encoderUnits::counts);
pros::ADIDigitalIn limitSwitch(LIMIT_SWITCH);
ControllerButton launch(ControllerDigital::A);
ControllerButton intakeRun(ControllerDigital::R1);
ControllerButton intakeRunBackwards(ControllerDigital::R2);
bool shoot;

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
                pros::delay(100);
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
