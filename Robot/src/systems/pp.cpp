#include "main.h"

namespace pp
{
    int lastIndex = 0;
    float kP = 1;
    const float robotWidth = 25.4;
    const float lookAhead = 10;
    const float linearVel = 5000; //voltages
    double angularVel;

    double t, t_i;

    // void ppStep1(std::vector<std::vector<double>> path, point currentPos, double currentHeading, float lookAhead, int lastIndex);
    void runpp(std::vector<std::vector<double>> path);
    // double closest(std::vector<std::vector<double>> path, point pos);
    // point lookAhead_f(std::vector<std::vector<double>> path, point pos, double t, double t_i);
    // double curvature(point lookAhead);
}



// void pp::ppStep1(std::vector<std::vector<double>> path, point currentPos, double currentHeading, float lookAhead, int lastIndex)
// {
//     float x, y;
//     float x1, y1, x2, y2, dx, dy, dr, D, discriminant;
//     float x1_s, y1_s, x2_s, y2_s;
//     float minX, minY, maxX, maxY;
//     double targetAngle, error_a;
//     double output;
//     bool foundIntersection = false;
//     float pt1_s[2], pt2_s[2], pt_goal[2];

//     std::tie(x, y) = currentPos;

//     printf("%f, %f", x, y);
//     int startIndex = lastIndex;

//     for (int i = 0; i < path.size() - 1; i++)
//     {
//         x1 = path[i][0] - x;
//         y1 = path[i][1] - y;
//         x2 = path[i + 1][0] - x;
//         y2 = path[i + 1][1] - y;
//         dx = x2 - x1;
//         dy = y2 - y1;
//         dr = pow(pow(dx, 2.0) + pow(dy, 2.0), 0.5);
//         D = x1 * y2 - x2 * y1;
//         discriminant = pow(lookAhead, 2.0) * pow(dr, 2.0) - pow(D, 2.0);

//         if (discriminant >= 0)
//         {
//             x1_s = ((D * dy + sgn(dy) * dx * pow(discriminant, 0.5)) / pow(dr, 2.0));
//             x2_s = ((D * dy - sgn(dy) * dx * pow(discriminant, 0.5)) / pow(dr, 2.0));
//             y1_s = ((-D * dx + fabs(dy) * pow(discriminant, 0.5)) / pow(dr, 2.0));
//             y2_s = ((-D * dx - fabs(dy) * pow(discriminant, 0.5)) / pow(dr, 2.0));

//             pt1_s[0] = x1_s + x;
//             pt1_s[1] = y1_s + y;
//             pt2_s[0] = x2_s + x;
//             pt1_s[1] = y2_s + y;

//             minX = std::min(path[i][0], path[i + 1][0]);
//             minY = std::min(path[i][1], path[i + 1][1]);
//             maxX = std::max(path[i][0], path[i + 1][0]);
//             maxY = std::max(path[i][1], path[i + 1][1]);

//             if (((minX <= pt1_s[0] <= maxX) && (minY <= pt1_s[1] <= maxY)) || ((minX <= pt2_s[0] <= maxX) && (minY <= pt2_s[1] <= maxY)))
//             {
//                 foundIntersection = true;

//                 if (((minX <= pt1_s[0] <= maxX) && (minY <= pt1_s[1] <= maxY)) && ((minX <= pt2_s[0] <= maxX) && (minY <= pt2_s[1] <= maxY)))
//                 {
//                     if (distanceToPoint({pt1_s[0], pt1_s[1]}, {path[i + 1][0], path[i + 1][1]}) < distanceToPoint({pt2_s[0], pt2_s[1]}, {path[i + 1][0], path[i + 1][1]}))
//                     {
//                         pt_goal[0] = pt1_s[0];
//                         pt_goal[1] = pt1_s[1];
//                     }
//                     else
//                     {
//                         pt_goal[0] = pt2_s[0];
//                         pt_goal[1] = pt2_s[1];
//                     }
//                 }
//                 else
//                 {
//                     if ((minX <= pt1_s[0] <= maxX) && (minY <= pt1_s[1] <= maxY))
//                     {
//                         pt_goal[0] = pt1_s[0];
//                         pt_goal[1] = pt1_s[1];
//                     }
//                     else
//                     {
//                         pt_goal[0] = pt2_s[0];
//                         pt_goal[1] = pt2_s[1];
//                     }
//                 }

//                 if (distanceToPoint({pt_goal[0], pt_goal[1]}, {path[i + 1][0], path[i + 1][1]}) < distanceToPoint({x, y}, {path[i + 1][0], path[i + 1][1]}))
//                 {
//                     pp::lastIndex = i;
//                     break;
//                 }
//                 else
//                 {
//                     pp::lastIndex = i + 1;
//                 }
//             }
//             else
//             {
//                 foundIntersection = false;
//                 pt_goal[0] = path[pp::lastIndex][0];
//                 pt_goal[1] = path[pp::lastIndex][1];
//             }
//         }
//     }

//     targetAngle = atan2(pt_goal[1] - y, pt_goal[0] - x);
//     if (targetAngle < 0)
//     {
//         targetAngle += 360;
//     }

//     error_a = targetAngle - currentHeading;
//     if (error_a >= 180 || error_a < -180)
//     {
//         error_a = -1 * sgn(error_a) * (360 - fabs(error_a));
//     }

//     output = ((pp::robotWidth * sin(degToRad(error_a))) / pp::lookAhead) * pp::linearVel * pp::kP;

//     pp::angularVel = output;
// }

void pp::runpp(std::vector<std::vector<double>> path)
{
    while (pp::lastIndex <= path.size() - 2)
    {
        pp::ppStep1(path, {odom::y, odom::x}, gyro2.get_heading(), pp::lookAhead, pp::lastIndex);
        std::cout << pp::angularVel << ", " << pp::lastIndex << std::endl;
        Ldrive.moveVoltage(pp::linearVel + pp::angularVel);
        Rdrive.moveVoltage(pp::linearVel - pp::angularVel);
        pros::delay(20);
    }
}

// double pp::closest(std::vector<std::vector<double>> path, point pos)
// {
//     double d_min[2]; // index and then actual value
//     double p[2];
//     double d;

//     d_min[0] = 0;
//     d_min[1] = distanceToPoint({path[0][0], path[0][1]}, pos);

//     for (int i = 0; i < path.size(); i++)
//     {
//         p[0] = path[i][0];
//         p[1] = path[i][1];
//         d = distanceToPoint({p[0], p[1]}, pos);

//         if (d < d_min[1])
//         {
//             d_min[0] = i;
//             d_min[1] = d;
//         }
//     }

//     return d_min[0];
// }

// point pp::lookAhead_f(std::vector<std::vector<double>> path, point currentPos, double t, double t_i)
// {
//     float x, y;
//     float x1, y1, x2, y2, dx, dy, dr, D, discriminant;
//     float x1_s, y1_s, x2_s, y2_s;
//     float minX, minY, maxX, maxY;
//     double targetAngle, error_a;
//     double output;
//     bool foundIntersection = false;
//     float pt1_s[2], pt2_s[2], pt_goal[2];

//     std::tie(x, y) = currentPos;

//     printf("%f, %f", x, y);
//     int startIndex = lastIndex;

//     for (int i = 0; i < path.size() - 1; i++)
//     {
//         x1 = path[i][0] - x;
//         y1 = path[i][1] - y;
//         x2 = path[i + 1][0] - x;
//         y2 = path[i + 1][1] - y;
//         dx = x2 - x1;
//         dy = y2 - y1;
//         dr = pow(pow(dx, 2.0) + pow(dy, 2.0), 0.5);
//         D = x1 * y2 - x2 * y1;
//         discriminant = pow(lookAhead, 2.0) * pow(dr, 2.0) - pow(D, 2.0);

//         if (discriminant >= 0)
//         {
//             x1_s = ((D * dy + sgn(dy) * dx * pow(discriminant, 0.5)) / pow(dr, 2.0));
//             x2_s = ((D * dy - sgn(dy) * dx * pow(discriminant, 0.5)) / pow(dr, 2.0));
//             y1_s = ((-D * dx + fabs(dy) * pow(discriminant, 0.5)) / pow(dr, 2.0));
//             y2_s = ((-D * dx - fabs(dy) * pow(discriminant, 0.5)) / pow(dr, 2.0));

//             pt1_s[0] = x1_s + x;
//             pt1_s[1] = y1_s + y;
//             pt2_s[0] = x2_s + x;
//             pt1_s[1] = y2_s + y;

//             minX = std::min(path[i][0], path[i + 1][0]);
//             minY = std::min(path[i][1], path[i + 1][1]);
//             maxX = std::max(path[i][0], path[i + 1][0]);
//             maxY = std::max(path[i][1], path[i + 1][1]);

//             if (((minX <= pt1_s[0] <= maxX) && (minY <= pt1_s[1] <= maxY)) || ((minX <= pt2_s[0] <= maxX) && (minY <= pt2_s[1] <= maxY)))
//             {
//                 foundIntersection = true;

//                 if (((minX <= pt1_s[0] <= maxX) && (minY <= pt1_s[1] <= maxY)) && ((minX <= pt2_s[0] <= maxX) && (minY <= pt2_s[1] <= maxY)))
//                 {
//                     if (distanceToPoint({pt1_s[0], pt1_s[1]}, {path[i + 1][0], path[i + 1][1]}) < distanceToPoint({pt2_s[0], pt2_s[1]}, {path[i + 1][0], path[i + 1][1]}))
//                     {
//                         pt_goal[0] = pt1_s[0];
//                         pt_goal[1] = pt1_s[1];
//                     }
//                     else
//                     {
//                         pt_goal[0] = pt2_s[0];
//                         pt_goal[1] = pt2_s[1];
//                     }
//                 }
//                 else
//                 {
//                     if ((minX <= pt1_s[0] <= maxX) && (minY <= pt1_s[1] <= maxY))
//                     {
//                         pt_goal[0] = pt1_s[0];
//                         pt_goal[1] = pt1_s[1];
//                     }
//                     else
//                     {
//                         pt_goal[0] = pt2_s[0];
//                         pt_goal[1] = pt2_s[1];
//                     }
//                 }
//                 return {pt_goal[0], pt_goal[1]};
//             }
//             else
//             {
//                 return {path[pp::closest(path, currentPos)][0], path[pp::closest(path, currentPos)][1]};
//             }
//         }
//     }
// }

// double pp::curvature(std::vector<std::vector<double>> path, point currentPos, point lookAhead)
// {
//     int side = sgn(sin(pi/2 - degToRad(gyro2.get_heading())) * (lookAhead.first - currentPos.first) - cos(pi/2 - degToRad(gyro2.get_heading())) * (lookAhead.first - currentPos.first));
//     double a = -tan(pi / 2 - degToRad(gyro2.get_heading()));
//     double c = tan(pi / 2 - degToRad(gyro2.get_heading())) * currentPos.first - currentPos.second;
//     double x = fabs(-tan(pi / 2 - degToRad(gyro2.get_heading())) * lookAhead.first + lookAhead.second + tan(pi / 2 - degToRad(gyro2.get_heading())) * currentPos.first - currentPos.second) / pow(pow(tan(pi / 2 - degToRad(gyro2.get_heading())), 2.0) + 1, 0.5);
//     x = fabs(a * lookAhead.first + lookAhead.second + c) / pow(pow(a, 2.0) + 1, 0.5);

//     return side * (2 * x / pow(pp::lookAhead, 2.0));
// }  