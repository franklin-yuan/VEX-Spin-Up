#include "main.h"
int sgn(double x) {
    if (x > 0){return 1;}
    else if (x < 0){return -1;}
    else {return 0;}
}

double constrainAngle(double angle) {
    return atan2(sin(angle * pi / 180), cos(angle * pi / 180)) * 180 / pi;
}

double degToRad(double x) {
    x = x * (pi / 180);
    return x;
}

double radToDeg(double x) {
    x = x / (pi / 180);
    return x;
}

double distanceToPoint(point pt1, point pt2) {
    double pt1x, pt1y, pt2x, pt2y;

    pt1x = pt1.first; pt1y = pt1.second;
    pt2x = pt2.first; pt2y = pt2.second;

    return pow(pow(pt2x - pt1x, 2) + pow(pt2y - pt1y, 2), 0.5);

}

/*
@param angle DEGREES
*/
double angleToBearing(double angle) {
    if (sgn(angle) > 0){
        return 90 - angle;
    }
    else if (sgn(angle) < 0){
        return angle - 90;
    }
    else{
        return angle;
    }
}      

