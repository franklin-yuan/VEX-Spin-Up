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

    double max = 100;

    while (count < 5){
        currentAngle = gyro2.get_heading();

        error = theta_d - currentAngle;

        error = constrainAngle(error);

        derivative = (constrainAngle(error - lastError));

        integral += error;

        output = (error*kP/360)+(derivative/360*kD)+((integral*kI)/360);
        output = std::clamp(output, -max, max);

        chassis->rotate(output);

        count = fabs(error) < 1 ? count + 1: 0;

        lastError = error;

        max += 6;

        pros::delay(20);

    }

    chassis->stop();

    
}

void pidDrive(float distance, double angle){
    
    float leftEnc, rightEnc, leftEnc_init, rightEnc_init;

    leftEnc_init = leftEncoder.get_value();
    rightEnc_init = rightEncoder.get_value();
    leftEnc = (leftEncoder.get_value() - leftEnc_init) * DEGREES_TO_CM;
    rightEnc = (rightEncoder.get_value() - rightEnc_init) * DEGREES_TO_CM;

    float currentDistance = (leftEnc + rightEnc) / 2;
    double currentAngle;

    double derivative_d, integral_d;
    double derivative_a, integral_a;
    double output_d, output_a;
    double output_d_l, output_d_r;
    int count = 0;

    float error_d = distance - currentDistance;
    float error_a = angle - currentAngle;

    float lastError_d = error_d;
    float lastError_a = error_a;

    float kP_d = 3.5;
    float kD_d = 0.1;
    float kI_d = 0;

    float kP_a = 0.15;
    float kD_a = 0;
    float kI_a = 0;

    double max_l = 6000;
    double max_r = 7200;

    while (count < 5){
        leftEnc = fabs((leftEncoder.get_value() - leftEnc_init) * DEGREES_TO_CM);
        rightEnc = fabs((rightEncoder.get_value() - rightEnc_init) * DEGREES_TO_CM);

        currentDistance = (leftEnc + rightEnc) / 2;

        currentAngle = constrainAngle(gyro2.get_heading());

        error_d = distance - currentDistance;
        error_a = angle - currentAngle;
        error_a = constrainAngle(error_a);

        derivative_d = error_d - lastError_d;
        derivative_a = error_a - lastError_a;
        
        integral_d += error_d;
        integral_a += error_a;
    
        output_d = (error_d*100*kP_d)+(derivative_d*100*kD_d)+((integral_d*100*kI_d));
        output_a = (error_a*360*kP_a)+(derivative_a*360*kD_a)+((integral_a*360*kI_a));


        output_d_l = std::clamp(output_d, -max_l, max_l);
        output_d_r = std::clamp(output_d, -max_r, max_r);
        output_d_l = std::clamp(output_d_l, -10000.0, 10000.0);
        output_d_r = std::clamp(output_d_r, -10000.0, 10000.0);
        double motorL = output_d_l + output_a;
        double motorR = output_d_r - output_a;
        //motorL = std::clamp(motorL, -max, max);
        //motorR = std::clamp(motorR, -max, max);

        Ldrive.moveVoltage(motorL);
        Rdrive.moveVoltage(motorR);

        float lastError_d = error_d;
        float lastError_a = error_a;

        count = fabs(error_d) < 2 ? count + 1: 0;
        max_l += 150;
        max_r += 150;
        pros::delay(10);
    }

    chassis->stop();

    
}