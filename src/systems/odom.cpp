#include "main.h"

pros::ADIEncoder leftEncoder (LEFT_ENCODER_TOP, LEFT_ENCODER_BOTTOM, true);
pros::ADIEncoder rightEncoder (RIGHT_ENCODER_TOP, RIGHT_ENCODER_BOTTOM, false);
pros::ADIEncoder backEncoder (BACK_ENCODER_TOP, BACK_ENCODER_BOTTOM, true);

void odom::updatePos(float left, float right, float side, float gyro){
    float dL = (left - odom::leftL) * DEGREES_TO_CM;
    float dR = (right - odom::rightL) * DEGREES_TO_CM;
    float dS = (side - odom::sideL) * DEGREES_TO_CM;

    odom::leftL = left;
    odom::rightL = right;
    odom::sideL = side;

    float hyp, hypS, r, rS, dTheta, dThetaGyro;

    dThetaGyro = gyro - gyroL;
    dTheta = (dL - dR) / (odom::d1 + odom::d2); //radians
    dTheta = (dTheta + dThetaGyro) / 2; //average gyro and encoder readings

    if (dTheta != 0){
        r = dR / dTheta; //radius of arc by right side enc
        hyp = ((r + odom::d2) * sin(dTheta / 2.0)) * 2.0;

        rS = dS / dTheta;
        hypS = ((rS + odom::d3) * sin(dTheta / 2.0)) * 2.0;

    }
    else{

        hyp = dR;
        dTheta = 0;

        hypS = dS;

    }

    double newHeading = dTheta + odom::theta;

    double dX = sin(newHeading) * hyp;
    double dY = cos(newHeading) * hyp;

    odom::x += dX;
    odom::y += dY;
    odom::theta = newHeading;
    odom::gyroL = gyro;
}

void runOdomTracking(){
    float left = leftEncoder.get_value();
    float right = rightEncoder.get_value();
    float back = backEncoder.get_value();

    double inertial = degToRad(constrainAngle(gyro.get_heading()));
    odom::updatePos(left, right, back, inertial);
    pros::delay(20);
}

void odom::printPos(){
    std::cout << "(" << odom::x << "," << odom::y << "," << odom::theta << ")" << std::endl;
    pros::lcd::print(1,"(%f,%f,%f degrees)",odom::x,odom::y,odom::theta);
}

void odom::resetEncoders(){
    leftEncoder.reset(); rightEncoder.reset(); backEncoder.reset();
}

void odom::printEncoders(){
    double left = leftEncoder.get_value(); 
    double right = rightEncoder.get_value();
    double back = backEncoder.get_value();
    pros::lcd::print(2,"(%f,%f,%f)", left,right,back);
    std::cout << "Left: " << left << "Right: " << right << "Back: " << back << std::endl;
}