#include "main.h"


bool skillsEnabled = false;
bool testAuton = true;
/**
 * Runs initialization code. This occurs as soon as the program is started.
 *
 * All other competition modes are blocked by initialize; it is recommended
 * to keep execution time for this mode under a few seconds.
 */
void initialize() {
    gyro1.reset();
    gyro2.reset();
    // while (gyro1.is_calibrating() || gyro2.is_calibrating()) {
    //     pros::delay(20);
    // }
    while (gyro2.is_calibrating()) {
        pros::delay(20);
    }
    odom::resetEncoders();
    // pros::Task trackOdom (runOdomTracking);
}

/**
 * Runs while the robot is in the disabled state of Field Management System or
 * the VEX Competition Switch, following either autonomous or opcontrol. When
 * the robot is enabled, this task will exit.
 */
void disabled() {

}

/**
 * Runs after initialize(), and before autonomous when connected to the Field
 * Management System or the VEX Competition Switch. This is intended for
 * competition-specific initialization routines, such as an autonomous selector
 * on the LCD.
 *
 * This task will exit when the robot is enabled and autonomous or opcontrol
 * starts.
 */
void competition_initialize() {
    drawAutonSelector();
}

/**
 * Runs the user autonomous code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the autonomous
 * mode. Alternatively, this function may be called in initialize or opcontrol
 * for non-competition testing purposes.
 *
 * If the robot is disabled or communications is lost, the autonomous task
 * will be stopped. Re-enabling the robot will restart the task, not re-start it
 * from where it left off.
 */
void autonomous() {
    pros::Task catapultTask(catapult);
    pros::Task odomTask(runOdomTracking);
	if(skillsEnabled){
		skills();
	}else if(testAuton){
		//WHATEVER AUTON TO TEST
		teamL(true);
	}else{
		if(autonEnabled){
			if(redAlliance){
				if(rollerDifficulty == 1){
					teamL(false);
				}
                else if(Hard){
                    carry(false);
                }
                else{
					teamR(false);
				}
			}else{
				if(rollerDifficulty == 1){
					teamL(true);
				}
                else if(Hard){
                    carry(true);
                }
                else{
					teamR(true);
				}
			}
		}
	}
}

/**
 * Runs the operator control code. This function will be started in its own task
 * with the default priority and stack size whenever the robot is enabled via
 * the Field Management System or the VEX Competition Switch in the operator
 * control mode.
 *
 * If no competition control is connected, this function will run immediately
 * following initialize().
 *
 * If the robot is disabled or communications is lost, the
 * operator control task will be stopped. Re-enabling the robot will restart the
 * task, not resume it from where it left off.
 */
void opcontrol() {
    pros::Task catapultTask(catapult);
    pros::Task odomTask(runOdomTracking);
    
    // for (int i = 1; i < path.size(); i++){
    //     std::cout << path[i][0] << path[i][1] << path[i][2] << path[i][3] << std::endl;

    //     odom::ramseteManual(path[i][0], path[i][1], 0, path[i][2], path[i][3], 2, 0.7);
    // }

    // pidTurn(90, 2.4, 2, 0);
    // pidTurn(0, 2.4, 2, 0);
    // pidTurn(180, 2.4, 2, 0);
    // pidTurn(-180, 2.4, 2, 0);

    // pidDrive(100, 0);
    // setIntake(170);
    // pidTurn(180, 2.4, 2, 0);
    // pidDrive(100, 180);
    // pidTurn(0, 2.4, 2, 0);
    //roll(false);

    while (true) {
        opDrive();
        intakeControl();
        shootExpansion();
        enableBoostOp();
        //oproll(true);
        odom::printPos();
        pros::delay(20);
    }
}
