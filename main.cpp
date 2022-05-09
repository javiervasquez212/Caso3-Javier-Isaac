#include <iostream>
#include "Router.h"

using namespace std;

int main(){
    vector<Coordinate> test;

    Coordinate p1 = Coordinate(30,25);
    Coordinate p2 = Coordinate(50, 20);
    Coordinate p3 = Coordinate(163, 225);
    Coordinate p4 = Coordinate(422, 100);
    Coordinate p5 = Coordinate(325, 10);
    Coordinate p6 = Coordinate(333, 276);

    test.push_back(p1);
    test.push_back(p2);
    test.push_back(p3);
    test.push_back(p4);
    test.push_back(p5);
    test.push_back(p6);

    Router routes = Router();
    routes.calculateRoutes(test);

    return 0;
}