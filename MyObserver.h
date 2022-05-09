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
    virtual void update();
};

MyObserver::MyObserver(/* args */)
{
}

MyObserver::~MyObserver()
{
}

void MyObserver::update(){
    cout << "Hice el update" << endl;
}


#endif