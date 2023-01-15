#include "main.h"

pros::ADIEncoder leftEncoder ({6 ,LEFT_ENCODER_TOP, LEFT_ENCODER_BOTTOM}, true);
pros::ADIEncoder rightEncoder ({6 , RIGHT_ENCODER_TOP, RIGHT_ENCODER_BOTTOM}, true);
pros::ADIEncoder sideEncoder (SIDE_ENCODER_TOP, SIDE_ENCODER_BOTTOM, true);

namespace odom{
    static float d1 = 18.75; //left to center, cm
    static float d2 = 18.75; //right to center, cm
    static float d3 = 17; //back to center, cm

    double x, y, theta;
    double leftL, rightL, sideL, gyroL;

    void updatePos(float left, float right, float side, float gyro);
    void printPos();
    void resetEncoders();
    void printEncoders();
}

void odom::updatePos(float left, float right, float side, float gyro){
    float dL = (left - leftL) * DEGREES_TO_CM;
    float dR = (right - rightL) * DEGREES_TO_CM;
    float dS = (side - sideL) * DEGREES_TO_CM;

    leftL = left;
    rightL = right;
    sideL = side;

    float hyp, hypS, r, rS, dTheta, dThetaGyro;

    dThetaGyro = gyro - gyroL;
    dTheta = (dL - dR) / (d1 + d2); //radians
    dTheta = (dTheta + dThetaGyro) / 2; //average gyro and encoder readings

    if (dTheta != 0){
        r = dR / dTheta; //radius of arc by right side enc
        hyp = ((r + d2) * sin(dTheta / 2.0)) * 2.0;

        rS = dS / dTheta;
        hypS = ((rS + d3) * sin(dTheta / 2.0)) * 2.0;

    }
    else{

        hyp = dR;
        dTheta = 0;

        hypS = dS;

    }

    double newHeading = dTheta + theta;

    double dX = sin(newHeading) * hyp;
    double dY = cos(newHeading) * hyp;

    x += dX;
    y += dY;
    theta = newHeading;
    gyroL = gyro;
}

void odom::printPos(){
    std::cout << "(" << x << "," << y << "," << theta << ")" << std::endl;
    pros::lcd::print(1,"(%f,%f,%f degrees)",x,y,theta);
}

void odom::resetEncoders(){
    leftEncoder.reset(); rightEncoder.reset(); sideEncoder.reset();
}

void odom::printEncoders(){
    double left = leftEncoder.get_value(); 
    double right = rightEncoder.get_value();
    double side = sideEncoder.get_value();
    pros::lcd::print(2,"(%f,%f,%f)", left,right,side);
    std::cout << "Left: " << left << "Right: " << right << "side: " << side << std::endl;
}

void runOdomTracking(){

    while (true){
        float left = leftEncoder.get_value();
        float right = rightEncoder.get_value();
        float side = sideEncoder.get_value();

        double inertial = degToRad(constrainAngle(gyro.get_heading()));
        odom::updatePos(left, right, side, inertial);
        std::cout << "oooooo" << std::endl;
        pros::delay(50);
    }
}