#include <iostream>
#include <string>
#include <unistd.h>
#include <stdio.h>  /* printf, scanf, puts, NULL */
#include <stdlib.h> /* srand, rand */
#include <time.h>
#include <vector>
#include <math.h>  
#include "Route.h"
#define PI 3.14159265358979323846
using namespace std;

class RouteMaker{
    protected:
        string observer;
        vector<Route> routes;
        int x= 800;
        int y= 800;
    public:
        RouteMaker();
        RouteMaker(string pObserver);
        string getObserver();
        bool randomLine();
        void calculateRoutes(vector<Point> pData);
        Route createRoute(Point pPoint, int pMovement);
        Point createStep(Point pPoint, int pAngle, bool pLine, int xToMove, int yToMove, int xTarget, int yTarget);
        int getX();
        void setX(int pX);
        int getY();
        void setY(int pY);
};

RouteMaker::RouteMaker(){
    observer = "";
}

RouteMaker::RouteMaker(string pObserver){
    observer = pObserver;
}

bool RouteMaker::randomLine(){

    int straightLineSelector;
    bool straightLine;

    srand(time(NULL));

    straightLineSelector = rand() % 2;

    if(straightLineSelector == 0){
        straightLine = true;
    }else{
        straightLine = false;
    }
    //cout << straightLine << endl;
    return straightLine;
}

void RouteMaker::calculateRoutes(vector<Point> pData){
    int movementSize = (this->x + this->y)/16;
    for(int i = 0; i <pData.size(); i++){
        Point initial = pData[i];
        Route routeToAdd = createRoute(initial, movementSize);
        routes.push_back(routeToAdd);
    }
    for(int j = 0; j <routes.size(); j++){
        Route initial = routes[j];
        initial.showInfo();
    }
}

Route RouteMaker::createRoute(Point pPoint, int pMovement){
    Route routeResult = Route();

    routeResult.addPoint(pPoint);

    int angle = 90;
    bool line = randomLine();

    float radAngle = angle * PI / 180;
    float xMovement = cos(radAngle)*pMovement;
    float yMovement = sin(radAngle)*pMovement;

    int xTarget = pPoint.getPositionX() + xMovement;
    int yTarget = pPoint.getPositionY() + yMovement;

    int steps = 10;
    int counter = 0;

    bool creatingRoute = true;

    int xToMove = ceil(xMovement/steps);
    int yToMove = ceil(yMovement/steps);

    cout << "xMovement: " << xMovement << "yMovement: " << yMovement << endl;
    cout << "xtoMove: " << xToMove << "yToMove: " << yToMove << endl;
    cout << "xDestino: " << xTarget << "yDestino: " << yTarget << endl;

    while(creatingRoute){

        Point temporaryPoint = routeResult.getLast();

        Point pointToAdd = createStep(temporaryPoint, angle, line, xToMove, yToMove, xTarget, yTarget);

        routeResult.addPoint(pointToAdd);

        if(pointToAdd.getPositionX() == xTarget && pointToAdd.getPositionY() == yTarget){
            creatingRoute = false;
        }
    }  

    return routeResult;
}

Point RouteMaker::createStep(Point pPoint, int pAngle, bool pLine, int xToMove, int yToMove, int xTarget, int yTarget){

    int newX = pPoint.getPositionX() + xToMove;
    int newY = pPoint.getPositionY() + yToMove;
    string newColor = pPoint.getColor();
    Point newPoint;

    if(xTarget - newX > xToMove){
        if(yTarget - newY > yToMove){
            newPoint = Point(newX, newY, newColor);
        }else{
            newPoint = Point(newX, yTarget, newColor);
        }
    }else{
        if(yTarget - newY > yToMove){
            newPoint = Point(xTarget, newY, newColor);
        }else{
            newPoint = Point(xTarget, yTarget, newColor);
        }
    }


    return newPoint;

}

//getters and setters
int RouteMaker::getX(){
    return this->x;
}

void RouteMaker::setX(int pX){
    this->x = pX;
}

int RouteMaker::getY(){
    return this->y;
}

void RouteMaker::setY(int pY){
    this->y = pY;
}

string RouteMaker::getObserver(){
    return observer;
}
