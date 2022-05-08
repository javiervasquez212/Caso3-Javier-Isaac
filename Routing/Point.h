#include <string>
#include <iostream>

using namespace std;

class Point
{
protected:
    int positionX;
    int positionY;
    string color;

public:
    Point();
    Point(int pPositionX, int pPositionY, string pColor);
    int getPositionX();
    int getPositionY();
    string getColor();
};

Point::Point()
{
    positionX = 0;
    positionY = 0;
    color = "#000000";
}

Point::Point(int pPositionX, int pPositionY, string pColor)
{
    positionX = pPositionX;
    positionY = pPositionY;
    color = pColor;
}

int Point::getPositionX()
{
    return positionX;
}

int Point::getPositionY()
{
    return positionY;
}

string Point::getColor()
{
    return color;
}
