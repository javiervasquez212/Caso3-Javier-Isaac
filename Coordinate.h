
#ifndef _COORDINATE_
#define _COORDINATE_ 0

#include <iostream>
using namespace std;

class Coordinate{

    private:
    
        float x;
        float y;

    public:
    
        //Constructor

        Coordinate(){};

         Coordinate( float pX,  float pY){
             x = pX;
             y = pY;
        }
        //Setters

        void setX(float pX) {
        x = pX;
        }
        void setY(float pY) {
        y = pY;
        }

        //Getters

        float getX() {
        return x;
        }
        float getY() {
        return y;
        }
};

#endif