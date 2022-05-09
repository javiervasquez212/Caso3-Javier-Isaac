
#ifndef _SVGDATA_
#define _SVGDATA_ 0

#include "Coordinate.h"
#include "Range.h"
#include <iostream>
#include <stdio.h>

using namespace std;

class PathData{

    private:
        Coordinate minCoordinate;
        Coordinate maxCoordinate;
        Coordinate absoluteCoordinate;
        Range colors;
        string pathColor;
        string pathPoints;

    public:

    float x;
    float y;

        //Constructor

        PathData(){};
            
        //Setters

        void setPathColor(string pColor){
            pathColor = pColor;
        }
        void setPathPoints(string pPoints){
            pathPoints = pPoints;
        }
        void setAbsoluteCoordinate(Coordinate pAbsoluteCoordinate){
            absoluteCoordinate = pAbsoluteCoordinate;
        }
        void setMinCoordinate(Coordinate pMinCoordinate) {

            minCoordinate = pMinCoordinate;
        }
        void setMaxCoordinate(Coordinate pMaxCoordinate) {
            maxCoordinate = pMaxCoordinate;
        }
        void setColors(Range pColors){
            colors = pColors;
        }

        //Getters

        float getMinX() {
        return minCoordinate.getX();
        }
        float getMinY() {
        return minCoordinate.getY();
        }
        float getMaxX() {
        return maxCoordinate.getX();;
        }
        float getMaxY() {
        return maxCoordinate.getY();
        }
        Range getColors(){
            return colors;
        }
        string getPathColor(){
            return pathColor;
        }
        string getPathPoints(){
            return pathPoints;
        }
};

#endif