#include <iostream>
#include "Router.h"
#include "Selection.h"

using namespace std;

int main(){

    Selection selecter = Selection();
    Router router = Router();
    selecter.setObserver(router);
    router.setSubject(selecter);
    selecter.startSelection();
    router.calculateRoutes(selecter.getPathList());

    return 0;
}