#ifndef _SVGDATA_
#define _SVGDATA_ 0

#include "Coordinate.h"
#include "Range.h"
#include <iostream>
#include <stdio.h>
#include "Route.h"

using namespace std;

class PathData
{

private:
    Coordinate minCoordinate;
    Coordinate maxCoordinate;
    Coordinate absoluteCoordinate;
    Range colors;
    string pathColor;
    string pathPoints;
    Route route;
    vector<float> vectorCoordinatesX;
    vector<float> vectorCoordinatesY;

public:
    float x;
    float y;

    PathData(){};

    // Setters

    void setVectorX(vector<float> pVectorX){
        this->vectorCoordinatesX = pVectorX;
    }
    void setVectorY(vector<float> pVectorY){
        this->vectorCoordinatesY = pVectorY;
    }
    void setPathColor(string pColor)
    {
        pathColor = pColor;
    }
    void setPathPoints(string pPoints)
    {
        pathPoints = pPoints;
    }
    void setAbsoluteCoordinate(Coordinate pAbsoluteCoordinate)
    {
        absoluteCoordinate = pAbsoluteCoordinate;
    }
    void setMinCoordinate(Coordinate pMinCoordinate)
    {
        minCoordinate = pMinCoordinate;
    }
    void setMaxCoordinate(Coordinate pMaxCoordinate)
    {
        maxCoordinate = pMaxCoordinate;
    }
    void setColors(Range pColors)
    {
        colors = pColors;
    }

    // Getters

    vector<float> getVectorX(){
        return this->vectorCoordinatesX;
    }
    vector<float> getVectorY(){
        return this->vectorCoordinatesY;
    }

    float getMinX()
    {
        return minCoordinate.getX();
    }
    float getMinY()
    {
        return minCoordinate.getY();
    }
    float getMaxX()
    {
        return maxCoordinate.getX();
        ;
    }

    Coordinate getAbsoluteCoordinate(){
        return this->absoluteCoordinate;
    }

    float getMaxY()
    {
        return maxCoordinate.getY();
    }
    Range getColors()
    {
        return colors;
    }
    string getPathColor()
    {
        return pathColor;
    }
    string getPathPoints()
    {
        return pathPoints;
    }
    Route getRoute()
    {
        return route;
    }
    void setRoute(Route pRoute)
    {
        this->route = pRoute;
    }
};

#endif