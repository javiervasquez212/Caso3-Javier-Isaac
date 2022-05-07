
#ifndef _SVGDATA_
#define _SVGDATA_ 0

#include "Coordinate.h"
#include "Range.h"
#include <iostream>
#include <stdio.h>

using namespace std;

class PathData{

    private:
        Coordinate MinCoordinate;
        Coordinate MaxCoordinate;
        Coordinate AbsoluteCoordinate;
        Range Colors;
        string PathColor;
        string PathPoints;

    public:

    float x;
    float y;

        PathData(){};
            
        //Setters

        void setPathColor(string pColor){
            PathColor = pColor;
        }
        void setPathPoints(string pPoints){
            PathPoints = pPoints;
        }
        void setAbsoluteCoordinate(Coordinate pAbsoluteCoordinate){
            AbsoluteCoordinate = pAbsoluteCoordinate;
        }
        void setMinCoordinate(Coordinate pMinCoordinate) {

            MinCoordinate = pMinCoordinate;
        }
        void setMaxCoordinate(Coordinate pMaxCoordinate) {
            MaxCoordinate = pMaxCoordinate;
        }
        void setColors(Range pColors){
            Colors = pColors;
        }

        //Getters

        float getMinX() {
        return MinCoordinate.getX();
        }
        float getMinY() {
        return MinCoordinate.getY();
        }
        float getMaxX() {
        return MaxCoordinate.getX();;
        }
        float getMaxY() {
        return MaxCoordinate.getY();
        }
        Range getColors(){
            return Colors;
        }
        string getPathColor(){
            return PathColor;
        }
        string getPathPoints(){
            return PathPoints;
        }
};

#endif