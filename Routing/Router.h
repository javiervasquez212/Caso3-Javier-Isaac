#include <iostream>
#include <string>
#include <unistd.h>
#include <stdlib.h> /* srand, rand */
#include <time.h>
#include <vector>
#include <math.h>
#include "Route.h"
#include "Observer.h"
#define PI 3.14159265358979323846
using namespace std;

class Router : public Observer
{
protected:
    vector<Route> routes;
    int x = 800;
    int y = 800;

public:
    Router();
    Router(Subject pSubject);
    bool randomLine();
    void calculateRoutes(vector<Point> pData);
    Route createRoute(Point pPoint, int pMovement);
    Point createStep(Point pPoint, int pAngle, bool pLine, int xToMove, int yToMove, int xTarget, int yTarget);
    int getX();
    void setX(int pX);
    int getY();
    void setY(int pY);
    void update();
};

Router::Router()
{
}

Router::Router(Subject pSubject) : Observer(pSubject)
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

void Router::calculateRoutes(vector<Point> pData)
{
    int movementSize = (this->x + this->y) / 16;
    for (int i = 0; i < pData.size(); i++)
    {
        Point initial = pData[i];
        Route routeToAdd = createRoute(initial, movementSize);
        routes.push_back(routeToAdd);
    }
    for (int j = 0; j < routes.size(); j++)
    {
        Route initial = routes[j];
        initial.showInfo();
    }
}

Route Router::createRoute(Point pPoint, int pMovement)
{
    Route routeResult = Route();

    routeResult.addPoint(pPoint);

    int angle = 110;
    bool line = randomLine();

    float radAngle = angle * PI / 180;

    float xMovement;
    float yMovement;

    if (angle < 180)
    {
        xMovement = cos(radAngle) * pMovement;
        yMovement = sin(radAngle) * pMovement;
    }
    else
    {
        xMovement = sin(radAngle) * pMovement;
        yMovement = cos(radAngle) * pMovement;
    }

    int xTarget = pPoint.getPositionX() + xMovement;
    int yTarget = pPoint.getPositionY() + yMovement;

    int steps = 30;
    int counter = 0;

    bool creatingRoute = true;

    int xToMove = ceil(xMovement / steps);
    int yToMove = ceil(yMovement / steps);

    cout << "xMovement: " << xMovement << "yMovement: " << yMovement << endl;
    cout << "xtoMove: " << xToMove << "yToMove: " << yToMove << endl;
    cout << "xDestino: " << xTarget << "yDestino: " << yTarget << endl;

    while (creatingRoute)
    {

        Point temporaryPoint = routeResult.getLast();

        Point pointToAdd = createStep(temporaryPoint, angle, line, xToMove, yToMove, xTarget, yTarget);

        routeResult.addPoint(pointToAdd);

        if (pointToAdd.getPositionX() == xTarget && pointToAdd.getPositionY() == yTarget)
        {
            creatingRoute = false;
        }
    }

    return routeResult;
}

Point Router::createStep(Point pPoint, int pAngle, bool pLine, int xToMove, int yToMove, int xTarget, int yTarget)
{

    int newX = pPoint.getPositionX() + xToMove;
    int newY = pPoint.getPositionY() + yToMove;
    string newColor = pPoint.getColor();
    Point newPoint;

    if (xTarget - newX > xToMove)
    {
        if (yTarget - newY > yToMove)
        {
            newPoint = Point(newX, newY, newColor);
        }
        else
        {
            newPoint = Point(newX, yTarget, newColor);
        }
    }
    else
    {
        if (yTarget - newY > yToMove)
        {
            newPoint = Point(xTarget, newY, newColor);
        }
        else
        {
            newPoint = Point(xTarget, yTarget, newColor);
        }
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
