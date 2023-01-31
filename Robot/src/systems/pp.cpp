#include "main.h"

namespace pp
{
    int lastIndex = 0;
    float kP = 1;
    const float lookAhead = 1;
}

void ppStep(std::vector<std::vector<double>> path, point currentPoint, double currentHeading, float lookAhead, int lastIndex)
{
    float x, y;
    float x1, y1, x2, y2, dx, dy, dr, D, discriminant;
    float x1_s, y1_s, x2_s, y2_s;
    float minX, minY, maxX, maxY;
    double targetAngle, error_a;
    double output;
    bool foundIntersection = false;
    float pt1_s[2], pt2_s[2], pt_goal[2];

    std::tie(x, y) = currentPoint;

    int startIndex = lastIndex;

    for (int i = 0; i < path.size(); i++)
    {

        x1 = path[i][0] - x;
        y1 = path[i][1] - y;
        x2 = path[i + 1][0] - x;
        y2 = path[i + 1][1] - y;
        dx = x2 - x1;
        dy = y2 - y1;
        dr = pow(pow(dx, 2.0) + pow(dy, 2.0), 0.5);
        D = x1 * y2 - x2 * y1;
        discriminant = pow(lookAhead, 2.0) * pow(dr, 2.0) - pow(D, 2.0);

        if (discriminant >= 0)
        {
            x1_s = ((D * dy + sgn(dy) * dx * pow(discriminant, 0.5)) / pow(dr, 2.0));
            x2_s = ((D * dy - sgn(dy) * dx * pow(discriminant, 0.5)) / pow(dr, 2.0));
            y1_s = ((-D * dx + fabs(dy) * pow(discriminant, 0.5)) / pow(dr, 2.0));
            y2_s = ((-D * dx - fabs(dy) * pow(discriminant, 0.5)) / pow(dr, 2.0));

            pt1_s[0] = x1_s + x;
            pt1_s[1] = y1_s + y;
            pt2_s[0] = x2_s + x;
            pt1_s[1] = y2_s + y;

            minX = std::min(path[i][0], path[i + 1][0]);
            minY = std::min(path[i][1], path[i + 1][1]);
            maxX = std::max(path[i][0], path[i + 1][0]);
            maxY = std::max(path[i][1], path[i + 1][1]);

            if (((minX <= pt1_s[0] <= maxX) && (minY <= pt1_s[1] <= maxY)) || ((minX <= pt2_s[0] <= maxX) && (minY <= pt2_s[1] <= maxY)))
            {
                foundIntersection = true;

                if (((minX <= pt1_s[0] <= maxX) && (minY <= pt1_s[1] <= maxY)) && ((minX <= pt2_s[0] <= maxX) && (minY <= pt2_s[1] <= maxY)))
                {
                    if (distanceToPoint({pt1_s[0], pt1_s[1]}, {path[i + 1][0], path[i + 1][1]}) < distanceToPoint({pt2_s[0], pt2_s[1]}, {path[i + 1][0], path[i + 1][1]}))
                    {
                        pt_goal[0] = pt1_s[0];
                        pt_goal[1] = pt1_s[1];
                    }
                    else
                    {
                        pt_goal[0] = pt2_s[0];
                        pt_goal[1] = pt2_s[1];
                    }
                }
                else
                {
                    if ((minX <= pt1_s[0] <= maxX) && (minY <= pt1_s[1] <= maxY))
                    {
                        pt_goal[0] = pt1_s[0];
                        pt_goal[1] = pt1_s[1];
                    }
                    else
                    {
                        pt_goal[0] = pt2_s[0];
                        pt_goal[1] = pt2_s[1];
                    }
                }

                if (distanceToPoint({pt_goal[0], pt_goal[1]}, {path[i + 1][0], path[i + 1][1]}) < distanceToPoint({x, y}, {path[i + 1][0], path[i + 1][1]}))
                {
                    pp::lastIndex = i;
                    break;
                }
                else
                {
                    pp::lastIndex = i + 1;
                }
            }
            else
            {
                foundIntersection = false;
                pt_goal[0] = path[pp::lastIndex][0];
                pt_goal[1] = path[pp::lastIndex][1];
            }
        }
    }

    targetAngle = atan2(pt_goal[1] - y, pt_goal[0] - x);
    if (targetAngle < 0)
    {
        targetAngle += 360;
    }

    error_a = targetAngle - currentHeading;
    if (error_a >= 180 || error_a < -180)
    {
        error_a = -1 * sgn(error_a) * (360 - fabs(error_a));
    }

    output = pp::kP * error_a;
}
