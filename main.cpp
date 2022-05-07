#include <iostream>
#include <string>
#include "RouteMaker.h"

using namespace std;

int main(){

    vector<Point> test;

    Point p1 = Point(10,20, "");
    Point p2 = Point(50, 20, "");
    Point p3 = Point(163, 225, "");
    Point p4 = Point(422, 100, "");
    Point p5 = Point(325, 10, "");
    Point p6 = Point(333, 276, "");

    test.push_back(p1);
    /* test.push_back(p2);
    test.push_back(p3);
    test.push_back(p4);
    test.push_back(p5);
    test.push_back(p6); */

    RouteMaker routes = RouteMaker();
    routes.calculateRoutes(test);

    return 0;
};
