#ifndef _SUBJECT_
#define _SUBJECT_ 0

#include <string>
#include <iostream>
#include "Observer.h"

class Subject
{
protected:
    Observer observer;

public:
    Subject();
    void notify();
    void addObserver(Observer pObserver);
};

Subject::Subject()
{
}

void Subject::addObserver(Observer pObserver)
{
    this->observer = pObserver;
}

#endif