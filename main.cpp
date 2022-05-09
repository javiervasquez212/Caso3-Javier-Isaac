#include <iostream>
#include "Router.h"
#include "Selection.h"

using namespace std;

int main(){

    Selection * selecter = new Selection();
    Router * router = new Router();
    router->setSubject(selecter);
    selecter->setObserver(router);
    selecter->startSelection();

    return 0;
}