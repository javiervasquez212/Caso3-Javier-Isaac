#include "MyObserver.h"
#include <iostream>
#include "MySubject.h"

using namespace std;

class Observador : public MyObserver
{
private:
    /* data */
public:
    Observador(/* args */);
    ~Observador();
    void update();
};

Observador::Observador(/* args */)
{
}

Observador::~Observador()
{
}

void Observador::update()
{   
    MyObserver::update();
    cout << "Soy un observador" << endl;
}

class Sujeto : public MySubject
{
private:
public:
    Sujeto(/* args */);
    ~Sujeto();
    void notify();
};
Sujeto::Sujeto(/* args */)
{
}
Sujeto::~Sujeto()
{
}

void Sujeto::notify(){
    this->getObserver().update();
    
}

