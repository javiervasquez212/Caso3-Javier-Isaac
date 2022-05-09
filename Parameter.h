#ifndef _SEARCH_
#define _SEARCH_ 0

#include <iostream>
#include "Coordinate.h"

using namespace std;

class Parameter{

    private:
    
        Coordinate point;
        int color;

    public:

        //Constructor

        Parameter(){};

        Parameter(Coordinate pPoint, int pColor){
            point = pPoint;
            color = pColor;
        }
        //Setters

        void setPoints(Coordinate pPoint) {
        point = pPoint;
        }
        void setColor(int pColor) {
        color = pColor;
        }

        //Getters

        Coordinate getPoint() {
        return point ;
        }
        int getColor() {
        return color;
        }
};

#endif