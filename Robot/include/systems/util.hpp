#pragma once
#include "main.h"

typedef std::pair<double, double> point;

extern double constrainAngle(double angle);
extern double degToRad(double x);
extern double radToDeg(double x);
extern double distanceToPoint(point pt1, point pt2);
extern int sgn(double x);
