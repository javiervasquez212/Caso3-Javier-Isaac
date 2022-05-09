#include <iostream>
#include "Router.h"
#include "Selection.h"
#include "Generator.h"

using namespace std;

int main(){

    Selection * selecter = new Selection();
    Router * router = new Router();
    Generator * generator = new Generator();
    router->setAngle(45);
    router->setSteps(20);
    router->setSubject(selecter);
    selecter->setObserver(router);
    router->setObserver(generator);
    generator->setSubject(router);

    
    selecter->startSelection();

    return 0;
}