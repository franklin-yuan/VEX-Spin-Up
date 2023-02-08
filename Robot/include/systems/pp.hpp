#pragma once
#include "main.h"

namespace pp
{
    // void ppStep1(std::vector<std::vector<double>> path, point currentPoint, double currentHeading, float lookAhead, int lastIndex);
    // void runpp(std::vector<std::vector<double>> path);

    void runpp(std::vector<std::vector<double>> path, bool direction);
    void findClosest(std::vector<std::vector<double>> path, point pos);
    void lookAhead_f(std::vector<std::vector<double>> path, point pos);
    void findCurvature(point pos);
    std::pair<double, double> findMotorVel();
    
}