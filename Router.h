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
#include "MySubject.h"
#include "Selection.h"
#define PI 3.14159265358979323846
using namespace std;

class Router : public MyObserver
{
protected:
    vector<PathData *> data;
    int x = 800;
    int y = 800;
    Selection * subject;

public:
    Router();
    bool randomLine();
    void calculateRoutes(vector<PathData *> pData);
    Route createRoute(Coordinate pPoint, int pMovement);
    Coordinate createStep(Coordinate pPoint, float pXToMove, float pYToMove, float pXTarget, float pYTarget);
    int getX();
    void setX(int pX);
    int getY();
    void setY(int pY);
    void setSubject(Selection * pSubject);
    void update();
};

Router::Router() : MyObserver()
{
}

void Router::setSubject(Selection * pSubject)
{
    this->subject = pSubject;
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

void Router::calculateRoutes(vector<PathData *> pData)
{
    int movementSize = (this->x + this->y) / 10;
    for (int i = 0; i < pData.size(); i++)
    {
        PathData *pathRouted = pData[i];
        Coordinate initial = pathRouted->getAbsoluteCoordinate();
        Route routeToAdd = createRoute(initial, movementSize);
        pathRouted->setRoute(routeToAdd);
        pathRouted->getRoute().showInfo();
    }
}

Route Router::createRoute(Coordinate pPoint, int pMovement)
{
    Route routeResult = Route();
    routeResult.addPoint(pPoint);
    int angle = 230;
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
    int newSteps;

    if (xyToMove < 5)
    {
        float multiplier = 5 / xyToMove;
        xToMove = xToMove * multiplier;
        yToMove = yToMove * multiplier;
        newSteps = xMovement / xToMove;
    }

    int jumpCounter = (steps / newSteps) - 1;
    int jumpCounterAux = jumpCounter;

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
    this->data = this->subject->getPathList();
    calculateRoutes(data);
    cout << "=============> entre aqui en el update de router" << endl;
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
