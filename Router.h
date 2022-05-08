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
    Coordinate createStep(Coordinate pPoint, bool pLine, float xToMove, float yToMove, float xTarget, float yTarget);
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
    int movementSize = (this->x + this->y) / 16;
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

    int angle = 110;
    bool line = randomLine();

    float radAngle = angle * PI / 180;

    float xMovement = cos(radAngle) * pMovement;
    float yMovement = sin(radAngle) * pMovement;

    float xTarget = pPoint.getX() + xMovement;
    float yTarget = pPoint.getY() + yMovement;

    int steps = 30;
    int counter = 0;

    bool creatingRoute = true;

    float xToMove = xMovement / steps;
    float yToMove = yMovement / steps;

    cout << "xMovement: " << xMovement << "yMovement: " << yMovement << endl;
    cout << "xtoMove: " << xToMove << "yToMove: " << yToMove << endl;
    cout << "xDestino: " << xTarget << "yDestino: " << yTarget << endl;
    cout << "================================"<< endl;

    while (counter < steps)
    {

        Coordinate temporaryPoint = routeResult.getLast();

        Coordinate pointToAdd = createStep(temporaryPoint, line, xToMove, yToMove, xTarget, yTarget);

        routeResult.addPoint(pointToAdd);

        /* if (pointToAdd.getPositionX() - xTarget < 1 && pointToAdd.getPositionY() - yTarget < 1)
        {
            creatingRoute = false;
        } */
        counter++;
    }

    return routeResult;
}

Coordinate Router::createStep(Coordinate pPoint, bool pLine, float xToMove, float yToMove, float xTarget, float yTarget)
{
    float newX = pPoint.getX() + xToMove;
    float newY = pPoint.getY() + yToMove;
    Coordinate newPoint;

    newPoint = Coordinate(newX, newY);

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
