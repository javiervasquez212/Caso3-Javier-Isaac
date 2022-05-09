#ifndef _GENERATOR_
#define _GENERATOR_ 0

#include "Router.h"
#include "MyObserver.h"

using namespace std;

class Generator : public MyObserver
{
private:
    Router *router;
    vector<PathData *> data;
    vector<string> newPaths;

public:
    Generator();
    ~Generator();
    void setSubject(Router *pRouter);
    void update();
    void generateSVGS(int pLenght);
    void transformVectors(PathData *pPathData);
    string createCForPath(PathData *pPathData);
};

Generator::Generator()
{
}

Generator::~Generator()
{
}

void Generator::generateSVGS(int pLenght)
{
    for (int i = 1; i < pLenght; i++)
    {
        for (int j = 0; j<this->data.size(); j++){
            PathData * pathGenerating = this->data[j];
            /* transformVectors(pathGenerating);
            cout << "////////////////////////////////////////" << endl;
            cout << createCForPath(pathGenerating) << endl;
            cout << "////////////////////////////////////////" << endl; */
        }
    }
}

void Generator::transformVectors(PathData *pPathData)
{
    int sizeVectorX = pPathData->getVectorX().size();
    int sizeVectorY = pPathData->getVectorY().size();
    Coordinate absolute = pPathData->getAbsoluteCoordinate();

    vector<float> newVectorX;
    vector<float> newVectorY;

    if (sizeVectorX == sizeVectorY)
    {
        for (int i = 0; i < sizeVectorX; i++)
        {   
            newVectorX.push_back((pPathData->getVectorX()[i] - absolute.getX()) / 10);
            newVectorY.push_back((pPathData->getVectorY()[i] - absolute.getY()) / 10);
        }
        pPathData->setVectorX(newVectorX);
        pPathData->setVectorY(newVectorY);
    }
}

string Generator::createCForPath(PathData *pPathData)
{
    int sizeVectorX = pPathData->getVectorX().size();
    string resultC = "c ";
    for (int i = 0; i < sizeVectorX; i++)
    {
        string xString = to_string(pPathData->getVectorX()[i]);
        string yString = to_string(pPathData->getVectorY()[i]);
        resultC += xString + "," + yString + " ";
    }
    return resultC;
}

void Generator::setSubject(Router *pRouter)
{
    this->router = pRouter;
}

void Generator::update()
{
    this->data = this->router->getData();
    int lenght = data[0]->getRoute().size();
    generateSVGS(lenght);
}
#endif