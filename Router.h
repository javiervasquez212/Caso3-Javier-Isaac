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


/*
N = the number of pathData objects that Router recieve from selection
Partial Optimum = each step created for each route
Global Optimum = the whole route created
Stages = each time the function createStep is called we create a step based on the previous one in order to find the points
*/

class Router : public MyObserver, public MySubject
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
    vector<PathData *> getData();
};

//Constructor
Router::Router() : MyObserver()
{
}


//Function that generates a random bool to either create a curve line or a straight line
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
    return straightLine;
}

//====================Main Methods ===================================

/* Function that recieves all the data from the Selection process and then starts adding the route to each path
It also calculates how much pixels the paths are going to be moved */
void Router::calculateRoutes(vector<PathData *> pData)
{
    int movementSize = (this->x + this->y) / 10;
    for (int pathIndex = 0; pathIndex < pData.size(); pathIndex++)
    {
        PathData *pathRouted = pData[pathIndex];
        Coordinate initial = pathRouted->getAbsoluteCoordinate();
        Route routeToAdd = createRoute(initial, movementSize);
        pathRouted->setRoute(routeToAdd);
        pathRouted->getRoute().showInfo();
    }
}

/* 
Recieves the amount of pixels to be moved and the initial point
to start creating the route, calculating the exact destiny were the path
will finish its route based on the angle
 */ 
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

    int steps = 25; //AKA as Frames
    int stepsCompleted = 0;

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

    int jumpStepSize = (steps / newSteps) - 1;
    int remainingStepsToJump = jumpStepSize;

    while (stepsCompleted < steps)
    {
        Coordinate temporaryPoint = routeResult.getLast();
        Coordinate pointToAdd;

        if (remainingStepsToJump > 0)
        {
            pointToAdd = createStep(temporaryPoint, 0, 0, xTarget, yTarget);
            remainingStepsToJump--;
        }
        else
        {
            pointToAdd = createStep(temporaryPoint, xToMove, yToMove, xTarget, yTarget);
            remainingStepsToJump = jumpStepSize;
        }

        routeResult.addPoint(pointToAdd);
        stepsCompleted++;
    }

    return routeResult;
}

/*
Creates each step of the route based on the previous step
*/
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
/*
Method Update from the observer
*/
void Router::update()
{
    this->setX(this->subject->getSizeX());
    this->setY(this->subject->getSizeY());
    this->data = this->subject->getPathList();
    calculateRoutes(data);

}

//=================Getters and Setters ========================================
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

void Router::setSubject(Selection * pSubject)
{
    this->subject = pSubject;
}

vector<PathData *> Router::getData(){
    return this->data;
}

#endif
