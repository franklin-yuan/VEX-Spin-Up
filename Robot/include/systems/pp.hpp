#pragma once
#include "main.h"

namespace pp
{
    void ppStep1(std::vector<std::vector<double>> path, point currentPoint, double currentHeading, float lookAhead, int lastIndex);
    void runpp(std::vector<std::vector<double>> path);
}