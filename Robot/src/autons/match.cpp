#include "main.h"

void carry()
{
    driveUntilRoller();
    chassis->forward(0.005);
    roll(true);
    chassis->stop();
    pidDrive(-20, -90, 3000, 0.1);
    setIntake(-600);
    pp::runpp(path, true);
    pidTurnToPoint({50, -270}, 2.4, 2, 0, true);
    shootCata();

}
