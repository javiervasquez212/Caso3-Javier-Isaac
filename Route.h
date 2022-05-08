#ifndef _ROUTE_
#define _ROUTE_ 0

#include <string>
#include <iostream>
#include <vector>
#include "Coordinate.h"

using namespace std;

class Route
{
protected:
    vector<Coordinate> animationSteps;

public:
    Route();
    vector<Coordinate> getAnimationSteps();
    void addPoint(Coordinate pStep);
    Coordinate getLast();
    void showInfo();
};

Route::Route()
{
}

vector<Coordinate> Route::getAnimationSteps()
{
    return animationSteps;
}

void Route::addPoint(Coordinate pStep)
{
    animationSteps.push_back(pStep);
}

Coordinate Route::getLast()
{
    return animationSteps[animationSteps.size() - 1];
}

void Route::showInfo()
{
    cout << "===========RUTA===========" << endl;
    for (int i = 0; i < animationSteps.size(); i++)
    {
        cout << "( " << animationSteps[i].getX() << ", " << animationSteps[i].getY() << ")" << endl;
    }
    cout << "Size of the route: " << animationSteps.size() << endl;
    cout << "==========================" << endl;
}

#endif