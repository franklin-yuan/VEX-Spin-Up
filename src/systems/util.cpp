#include "main.h"

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

    std::tie(pt1x, pt2x) = pt1;
    std::tie(pt2x, pt2y) = pt2;

    return pow(pow(pt2x - pt1x, 2) + pow(pt2y - pt1y, 2), 0.5);

}