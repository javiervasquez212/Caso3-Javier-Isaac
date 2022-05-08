#ifndef _SEARCH_
#define _SEARCH_ 0

#include <iostream>
#include "Coordinate.h"

using namespace std;

class Parameter
{

private:
    Coordinate Point;
    int Color;

public:
    Parameter(){};

    Parameter(Coordinate pPoint, int pColor)
    {
        Point = pPoint;
        Color = pColor;
    }
    // Setters

    void setPoints(Coordinate pPoint)
    {
        Point = pPoint;
    }
    void setColor(int pColor)
    {
        Color = pColor;
    }

    // Getters

    Coordinate getPoint()
    {
        return Point;
    }
    int getColor()
    {
        return Color;
    }
};

#endif