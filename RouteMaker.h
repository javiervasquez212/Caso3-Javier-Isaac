#include <iostream>
#include <string>
#include <unistd.h>
#include <stdio.h>  /* printf, scanf, puts, NULL */
#include <stdlib.h> /* srand, rand */
#include <time.h>
using namespace std;

class RouteMaker{
    protected:
        string observer;
        bool straightLine;
    public:
        RouteMaker();
        RouteMaker(string pObserver);
        string getObserver();
        void randomLine();
        void calculateRoute();
};

RouteMaker::RouteMaker(){
    straightLine = true;
    observer = "";
}

RouteMaker::RouteMaker(string pObserver){
    straightLine = true;
    observer = pObserver;
}

string RouteMaker::getObserver(){
    return observer;
}

void RouteMaker::randomLine(){

    int straightLineSelector;

    srand(time(NULL));

    straightLineSelector = rand() % 2;

    if(straightLineSelector == 0){
        straightLine = true;
    }else{
        straightLine = false;
    }
    cout << straightLine << endl;
}