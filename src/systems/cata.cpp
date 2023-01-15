#include "main.h"
#define LIMIT_SWITCH 'A'
#define CATA_PORT 1

Motor cata(CATA_PORT, false, AbstractMotor::gearset::red, AbstractMotor::encoderUnits::counts);
pros::ADIDigitalIn limitSwitch(LIMIT_SWITCH);
ControllerButton launch(ControllerDigital::A);

void catapult() {
    while (true) {
        // If limit switch not pressed move down
        if (!limitSwitch.get_value()) {
            cata.moveVelocity(80);
        } else {
            if (launch.changedToReleased()) {
                while (limitSwitch.get_value()) {
                    cata.moveVelocity(80);
                }
                cata.moveVelocity(0);
            }
            cata.moveVelocity(0);
        }
        pros::Task::delay(20);
    }
}
