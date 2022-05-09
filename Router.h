#ifndef _ROUTER_
#define _ROUTER_ 0

#include <iostream>
#include <string>
#include <unistd.h>
#include <stdlib.h> /* srand, rand */
#include <time.h>
#include <vector>
#include <math.h>
#include "Route.h"
#define PI 3.14159265358979323846
using namespace std;

class Router
{
protected:
    vector<Route> routes;
    int x = 800;
    int y = 800;

public:
    Router();
    bool randomLine();
    void calculateRoutes(vector<Coordinate> pData);
    Route createRoute(Coordinate pPoint, int pMovement);
    Coordinate createStep(Coordinate pPoint, float pXToMove, float pYToMove, float pXTarget, float pYTarget);
    int getX();
    void setX(int pX);
    int getY();
    void setY(int pY);
    void update();
};

Router::Router()
{
}

bool Router::randomLine()
{

    int straightLineSelector;
    bool straightLine;

    srand(time(NULL));

    straightLineSelector = rand() % 2;

    if (straightLineSelector == 0)
    {
        straightLine = true;
    }
    else
    {
        straightLine = false;
    }
    // cout << straightLine << endl;
    return straightLine;
}

void Router::calculateRoutes(vector<Coordinate> pData)
{
    int movementSize = (this->x + this->y) / 10;
    for (int i = 0; i < pData.size(); i++)
    {
        Coordinate initial = pData[i];
        Route routeToAdd = createRoute(initial, movementSize);
        routes.push_back(routeToAdd);
    }
    for (int j = 0; j < routes.size(); j++)
    {
        Route initial = routes[j];
        initial.showInfo();
    }
}

Route Router::createRoute(Coordinate pPoint, int pMovement)
{
    Route routeResult = Route();
    routeResult.addPoint(pPoint);
    int angle = 60;
    bool line = randomLine();
    float radAngle = angle * PI / 180;
    float xMovement = cos(radAngle) * pMovement;
    float yMovement = sin(radAngle) * pMovement;
    float xTarget = pPoint.getX() + xMovement;
    float yTarget = pPoint.getY() + yMovement;

    if (xTarget > this->x)
    {
        xTarget = this->x;
        xMovement = this->x - pPoint.getX();
    }

    if (yTarget > this->y)
    {
        yTarget = this->y;
        yMovement = this->y - pPoint.getY();
    }

    if (xTarget <= 0)
    {
        xTarget = 0;
        xMovement = -1 * pPoint.getX();
    }

    if (yTarget <= 0)
    {
        yTarget = 0;
        yMovement = -1 * pPoint.getY();
    }

    int steps = 25;
    int counter = 0;

    float xToMove = xMovement / steps;
    float yToMove = yMovement / steps;
    float xyToMove = sqrt(pow(xToMove, 2) + pow(yToMove, 2));
    float multiplier;
    int newSteps;

    if (xyToMove < 5)
    {
        multiplier = 5 / xyToMove;
        xToMove = xToMove * multiplier;
        yToMove = yToMove * multiplier;
        newSteps = xMovement / xToMove;
    }

    int jumpCounter = (steps / newSteps) - 1;
    int jumpCounterAux = jumpCounter;

    cout << "xMovement: " << xMovement << "| yMovement: " << yMovement << endl;
    cout << "xtoMove: " << xToMove << "| yToMove: " << yToMove << endl;
    cout << "xDestino: " << xTarget << "| yDestino: " << yTarget << endl;
    cout << "================================" << endl;

    while (counter < steps)
    {
        Coordinate temporaryPoint = routeResult.getLast();
        Coordinate pointToAdd;

        if (jumpCounterAux > 0)
        {
            pointToAdd = createStep(temporaryPoint, 0, 0, xTarget, yTarget);
            jumpCounterAux--;
        }
        else
        {
            pointToAdd = createStep(temporaryPoint, xToMove, yToMove, xTarget, yTarget);
            jumpCounterAux = jumpCounter;
        }

        routeResult.addPoint(pointToAdd);
        counter++;
    }

    return routeResult;
}

Coordinate Router::createStep(Coordinate pPoint, float pXToMove, float pYToMove, float pXTarget, float pYTarget)
{
    float newX = pPoint.getX() + pXToMove;
    float newY = pPoint.getY() + pYToMove;
    Coordinate newPoint;

    if ((pXToMove != 0) || (pYToMove != 0))
    {
        if (abs(newX - pXTarget) < 5)
        {
            newX = pXTarget;
        }
        if (abs(newY - pYTarget) < 5)
        {
            newY = pYTarget;
        }

        newPoint = Coordinate(newX, newY);
    }

    if ((pXToMove == 0) && (pYToMove == 0))
    {
        newPoint = pPoint;
    }

    return newPoint;
}
//===============UPDATE===================
void Router::update()
{
}

// getters and setters
int Router::getX()
{
    return this->x;
}

void Router::setX(int pX)
{
    this->x = pX;
}

int Router::getY()
{
    return this->y;
}

void Router::setY(int pY)
{
    this->y = pY;
}

#endif
