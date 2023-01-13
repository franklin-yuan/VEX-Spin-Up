#include "main.h"

double constrainAngle (double angle)
{
    return atan2(sin(angle*pi/180),cos(angle*pi/180))*180/pi;
}

double degToRad(double x){
    x = x * (pi/180);
    return x;
}

double radToDeg(double x){
    x = x / (pi / 180);
    return x;
}