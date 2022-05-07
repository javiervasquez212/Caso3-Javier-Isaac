
#ifndef _COORDINATE_
#define _COORDINATE_ 0

#include <iostream>
using namespace std;

class Coordinate{

    private:
        float X;
        float Y;

    public:
    
        //Constructor
        Coordinate(){};

         Coordinate( float pX,  float pY){
             X = pX;
             Y = pY;
        }
        //Setters

        void setX(float pX) {
        X = pX;
        }
        void setY(float pY) {
        Y = pY;
        }

        //Getters

        float getX() {
        return X;
        }
        float getY() {
        return Y;
        }
};

#endif