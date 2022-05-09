#ifndef _MYOBSERVER_
#define _MYOBSERVER_ 0

#include <iostream>

class MyObserver
{
private:
    /* data */
public:
    MyObserver(/* args */);
    ~MyObserver();
    virtual void update();
};

MyObserver::MyObserver(/* args */)
{
}

MyObserver::~MyObserver()
{
}



#endif