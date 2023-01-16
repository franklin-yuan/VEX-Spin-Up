#include "main.h"

pros::ADIEncoder leftEncoder({6, LEFT_ENCODER_TOP, LEFT_ENCODER_BOTTOM}, true);
pros::ADIEncoder rightEncoder({6, RIGHT_ENCODER_TOP, RIGHT_ENCODER_BOTTOM}, true);
pros::ADIEncoder sideEncoder(SIDE_ENCODER_TOP, SIDE_ENCODER_BOTTOM, true);

namespace odom {
    const float d1 = 7.5;  // left to center, cm
    const float d2 = 7.5;  // right to center, cm
    const float d3 = 1;    // back to center, cm

    double x, y, theta;
    double leftL, rightL, sideL, gyroL;

    void updatePos(float left, float right, float side, float gyro);
    void printPos();
    void resetEncoders();
    void printEncoders();
    void ramseteManual(double xd, double yd, double thetad);
}  

//pilons math, doesnt work

void odom::updatePosPilons(float left, float right, float side, float gyro) {
    float dL = (left - leftL) * DEGREES_TO_CM;
    float dR = (right - rightL) * DEGREES_TO_CM;
    float dS = (side - sideL) * DEGREES_TO_CM;

    leftL = left;
    rightL = right;
    sideL = side;

    float hyp, hypS, r, rS, dTheta, dThetaGyro;

    dThetaGyro = gyro - gyroL;
    dTheta = (dL - dR) / (d1 + d2);      // radians
    dTheta = (dTheta + dThetaGyro) / 2;  // average gyro and encoder readings

    if (dTheta != 0) {
        r = dR / dTheta;  // radius of arc by right side enc
        hyp = ((r + d2) * sin(dTheta / 2.0)) * 2.0;

        rS = dS / dTheta;
        hypS = ((rS + d3) * sin(dTheta / 2.0)) * 2.0;

    } else {
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

//good math

void odom::updatePos(float left, float right, float side, float gyro) {
    float dL = (left - leftL) * DEGREES_TO_CM;
    float dR = (right - rightL) * DEGREES_TO_CM;
    float dS = (side - sideL) * DEGREES_TO_CM;

    //delta encoder values

    leftL = left;
    rightL = right;
    sideL = side;

    //assign last variables

    float dtheta, dx, dy, newHeading;

    //delta theta, x, y, these are local
    //where x is forwards/backwards, y is left-right
    //newHeading is half of new heading for calculations

    dtheta = (dR - dL) / (d1 + d2);
    dx = (dR + dL) / 2.0;
    dy = (dS - (dR - dL) * d3 / ODOM_WHEEL_DIAMETER_CM);

    //change encoder vals to delta theta, x, y

    newHeading = theta + dtheta / 2.0;

    x += dx * cos(newHeading) - dy * sin(newHeading);
    y += dx * sin(newHeading) - dy * cos(newHeading);

    //add dx and dy while adding a rotation matrix to make them global

    theta += dtheta;
    theta = (theta + degToRad(gyro)) / 2;

    //add dtheta and also average with gyro vals
}

void odom::ramseteManual(double xd, double yd, double thetad){

    float threshold = 0.5;
    //how far from target to move on

    double dis = distanceToPoint({x,y},{xd,yd});

    while (dis > threshold){

        double xe_g, ye_g, thetae_g; //global error
        xe_g = xd - x; ye_g = yd - y; thetae_g = thetad - theta;

        double xe_l, ye_l, thetae_l; //local error
        
        //rotation matrix
        xe_l = xe_g * cos(theta) + ye_g * sin(theta);
        ye_l = xe_g * -sin(theta) + ye_g * cos(theta);
        thetae_l = thetae_g;

        // where x is forwards/backwards

        float beta, zeta;
        double vd, omegad;
        
        double omegaMax = 100;
        double vMax = 100;

        float k;
        //where beta > 0, and controls sensitivity
        // 0 < zeta < 1, dampens sensitivity
        // vd is the desired linear velocity
        // omegad is the desired angular velocity

        //k is a gain value

        float scalar = 0.01; 

        //for non-profiled movements, automatic estimation of vd and omegad

        vd = scalar * xe_l;
        omegad = scalar * thetae_l;

        k = 2 * zeta * pow(pow(omegad, 2) + beta * pow(vd, 2), 0.5);

        double v, omega;

        //where v and omega are output linear and angular velocities

        //apply gain to generate output v and omega
        v = vd * cos(thetae_l + k * xe_l);

        if (thetae_l != 0) {
            omega = omegad + k * thetae_l + (beta * vd * sin(thetae_l) * ye_l) / thetae_l;
        }
        else{
            omega = omegaMax;
        }

        //convert v and omega to left and right drive vals

        double v_motor, omega_motor;

        double left, right;
        //where v_motor is the linear velocity component of motor val, etc.
        //left and right are respective drive train vals

        left = v_motor + omega_motor;
        right = v_motor - omega_motor;

        float k = 300;
        
        left *= k; right *= k;

        //apply scaling value

        Ldrive.moveVoltage(left);
        Rdrive.moveVoltage(right);

        std::cout << "left:" << left << " right:" << right << std::endl;

        pros::delay(10);
    }
}

void odom::printPos() {
    std::cout << "(" << x << "," << y << "," << theta << ")" << std::endl;
    pros::lcd::print(1, "(%f,%f,%f degrees)", x, y, radToDeg(theta));
}

void odom::resetEncoders() {
    leftEncoder.reset();
    rightEncoder.reset();
    sideEncoder.reset();
}

void odom::printEncoders() {
    double left = leftEncoder.get_value();
    double right = rightEncoder.get_value();
    double side = sideEncoder.get_value();
    pros::lcd::print(2, "(%f,%f,%f)", left, right, side);
    std::cout << "Left: " << left << "Right: " << right << "side: " << side << std::endl;
}

void runOdomTracking() {
    while (true) {
        float left = leftEncoder.get_value();
        float right = rightEncoder.get_value();
        float side = sideEncoder.get_value();

        double inertial = degToRad(constrainAngle((gyro1.get_heading() + gyro2.get_heading()) / 2)); //average two gyros
        odom::updatePos(left, right, side, inertial);
        std::cout << "oooooo" << std::endl;
        pros::delay(50);
    }
}