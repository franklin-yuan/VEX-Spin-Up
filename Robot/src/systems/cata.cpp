#include "main.h"
#define LIMIT_SWITCH 'A'
#define CATA_PORT 18
#define INTAKE_PORT 10

Motor cata(CATA_PORT, false, AbstractMotor::gearset::red, AbstractMotor::encoderUnits::counts);
Motor intake(INTAKE_PORT, false, AbstractMotor::gearset::green, AbstractMotor::encoderUnits::counts);
pros::ADIDigitalIn limitSwitch(LIMIT_SWITCH);
ControllerButton launch(ControllerDigital::A);
ControllerButton intakeRun(ControllerDigital::R1);
ControllerButton intakeRunBackwards(ControllerDigital::R2);

void catapult() {
    while (true) {
        // If limit switch not pressed move down
        if (!limitSwitch.get_value()) {
            cata.moveVelocity(80);
        } else {
            if (launch.changedToReleased()) {
                while (limitSwitch.get_value()) {
                    cata.moveVelocity(30);
                }
                cata.moveVelocity(0);
            }
            cata.moveVelocity(0);
        }
        pros::Task::delay(20);
    }
}

void intakeControl() {
    if (intakeRun.isPressed()) {
        intake.moveVelocity(-200);
    }
    else if (intakeRunBackwards.isPressed()) {
        intake.moveVelocity(170);
    }
    else{
        intake.moveVelocity(0);
    }
}

void setIntake(int vel) {
    intake.moveVelocity(vel);
}
