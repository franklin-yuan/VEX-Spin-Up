#include "main.h"

void pidTurn(float theta_d, float kP, float kD, float kI){
    

    double derivative, integral = 0;
    double error, lastError;
    double currentAngle;
    double output;
    int count;

    currentAngle = gyro2.get_heading();

    error = theta_d - currentAngle;

    error = constrainAngle(error);

    lastError = error;

    while (count < 5){
        currentAngle = gyro2.get_heading();

        error = theta_d - currentAngle;

        error = constrainAngle(error);

        derivative = (constrainAngle(error - lastError));

        integral += error;

        output = (error*kP/360)+(derivative/360*kD)+((integral*kI)/360);

        chassis->rotate(output);

        count = fabs(error) < 1 ? count + 1: 0;

        lastError = error;

        pros::delay(20);

    }

    chassis->stop();

    
}

void pidDrive(float distance){
    
    float leftEnc, rightEnc;
    leftEnc = leftEncoder.get_value() * DEGREES_TO_CM;
    rightEnc = rightEncoder.get_value() * DEGREES_TO_CM;

    double derivative_l, derivative_r, integral_l, integral_r;
    double output_l, output_r;
    int count;

    float error_l = distance - leftEnc;
    float error_r = distance - rightEnc;

    float lastError_l = error_l;
    float lastError_r = error_r;

    float kP = 1;
    float kD = 0;
    float kI = 0;

    while (count < 5){
        leftEnc = leftEncoder.get_value() * DEGREES_TO_CM;
        rightEnc = rightEncoder.get_value() * DEGREES_TO_CM;

        float error_l = distance - leftEnc;
        float error_r = distance - rightEnc;

        derivative_l = error_l - lastError_l;
        derivative_r = error_r - lastError_r;
        
        output_l = (error_l*100*kP)+(derivative_l*100*kD)+((integral_l*100*kI));
        output_r = (error_r*100*kP)+(derivative_r*100*kD)+((integral_r*100*kI));

        Ldrive.moveVoltage(output_l);
        Rdrive.moveVoltage(output_r);

        float lastError_l = error_l;
        float lastError_r = error_r;


    }

    chassis->stop();

    
}