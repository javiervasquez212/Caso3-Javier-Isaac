#ifndef _MYSUBJECT_
#define _MYSUBJECT_ 0
#include <iostream>
#include "MyObserver.h"

using namespace std;

class MySubject
{
private:
    MyObserver observer;
public:
    MySubject(/* args */);
    ~MySubject();
    MyObserver getObserver();
    virtual void setObserver(MyObserver pObserver);
    virtual void notify();
};

MySubject::MySubject(/* args */)
{
}

MySubject::~MySubject()
{
}

MyObserver MySubject::getObserver(){
    return this->observer;
}

void MySubject::setObserver(MyObserver pObserver){
    this->observer = pObserver;
}

void MySubject::notify(){
    this->observer.update();
}


#endif