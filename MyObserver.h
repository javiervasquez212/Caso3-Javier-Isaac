#ifndef _MYOBSERVER_
#define _MYOBSERVER_ 0

#include <iostream>

using namespace std;

class MyObserver
{
private:
    /* data */
public:
    MyObserver(/* args */);
    ~MyObserver();
    virtual void update() = 0;
};

MyObserver::MyObserver(/* args */)
{
}

MyObserver::~MyObserver()
{
}

#endif