#include <string>
#include <iostream>
#include <vector>
#include "Point.h"

using namespace std;

class Route{
    protected:
        vector<Point> animationSteps;
    public:
        Route();
        vector<Point> getAnimationSteps();
        void addPoint(Point pStep);
        Point getLast();
        void showInfo();
};

Route::Route(){
}

vector<Point> Route::getAnimationSteps(){
    return animationSteps;
}

void Route::addPoint(Point pStep){
    animationSteps.push_back(pStep);
}

Point Route::getLast(){
    return animationSteps[animationSteps.size() - 1];
}

void Route::showInfo(){
    cout << "===========RUTA===========" << endl;
    for(int i = 0; i < animationSteps.size(); i++){
        cout << "( " << animationSteps[i].getPositionX() << ", " << animationSteps[i].getPositionY() << ")" <<endl;
    }
    cout << "Size of the route: " << animationSteps.size() << endl;
    cout << "==========================" << endl;
}
