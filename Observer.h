#ifndef _OBSERVER_
#define _OBSERVER_ 0

#include <string>
#include <iostream>
#include <vector>
#include "Subject.h"

using namespace std;

class Observer {
    protected:
        Subject subject; 
    public:
        Observer();
        Observer(Subject pSubject);
        virtual void update();
        void addSubject(Subject pSubject);
};

Observer::Observer(Subject pSubject){
    this->subject = pSubject;
}

void Observer::addSubject(Subject pSubject){
    this->subject = pSubject;
}

#endif