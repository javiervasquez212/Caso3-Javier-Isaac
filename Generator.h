#ifndef _GENERATOR_
#define _GENERATOR_ 0

#include "Router.h"
#include "MyObserver.h"


class Generator : public MyObserver
{
private:
    Router * router;
public:
    Generator(/* args */);
    ~Generator();
    void setSubject(Router * pRouter);
    void update();
};

Generator::Generator(/* args */)
{
}

Generator::~Generator()
{
}

#endif