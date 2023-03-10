#include "main.h"

pros::Optical colourSensor(9);
ControllerButton rollerButton(ControllerDigital::L1);

#define redHue 350
#define blueHue 215
#define threshold 10
#define rollerDist 220


/*
@param colour: true if blue, false if red
*/
void roll(bool colour)
{
    bool correctColour = false;
    bool atRoller = false;
    int hue; 
    int dist;
    setIntake(150);
    uint32_t startTime = pros::millis();
    while (!correctColour)
    {

        if((pros::millis()-startTime > 2000)){
            chassis->stop();
            break;
        }
        
        hue = colourSensor.get_hue();
        dist = colourSensor.get_proximity();

        atRoller = dist > rollerDist ? true : false;

        //std::cout << atRoller << std::endl;

        if (colour && atRoller){
            correctColour = (blueHue - threshold) < hue && hue < (blueHue + threshold) ? true : false;
        }
        else if (!colour && atRoller){
            correctColour = (redHue - threshold) < hue && hue < (redHue + threshold) ? true : false;
        }

        pros::delay(50);
    }
    pros::delay(200);
    setIntake(0);
}

/*
@param colour: true if blue, false if red, for teams
*/
void oproll(bool colour)
{

    bool correctColour = false;
    bool atRoller = false;
    int hue; 
    int dist;
    setIntake(80);

    if (rollerButton.isPressed()){
        while (!correctColour)
        {
            hue = colourSensor.get_hue();
            dist = colourSensor.get_proximity();

            atRoller = dist > rollerDist ? true : false;

            //std::cout << atRoller << std::endl;

            if (colour && atRoller){
                correctColour = (blueHue - threshold) < hue && hue < (blueHue + threshold) ? true : false;
            }
            else if (!colour && atRoller){
                correctColour = (redHue - threshold) < hue && hue < (redHue + threshold) ? true : false;
            }

            pros::delay(50);
        }
        pros::delay(400);
        setIntake(0);
    }
}
