#include <iostream>
#include <vector>
#include <string>

using namespace std;


vector<SVGData> vectorData;

class coordinate{

    private:
        float X;
        float Y;

    public:
        //Setters

        void setX(float pX) {
        X = pX;
        }
        void setY(float pY) {
        Y = pY;
        }

        //Getters

        float getX() {
        return X;
        }
        float getY() {
        return Y;
        }
};


class SVGData{

    private:
        coordinate MinCoordinate;
        coordinate MaxCoordinate;
        vector<string> Colors;

    public:

        //Constructor

        SVGData(coordinate pMin, coordinate pMax, vector<string> pColors){
            MinCoordinate = pMin;
            MaxCoordinate = pMax;
            Colors = pColors;
        }

        //Setters

        void setMinCoordinate(float pX, float pY) {
            MinCoordinate.setX(pX);
            MinCoordinate.setY(pY);
        }
        void setMaxCoordinate(float pX, float pY) {
            MaxCoordinate.setX(pX);
            MaxCoordinate.setY(pY);
        }
        void setColors(vector<string> pColors){
            Colors = pColors;
        }

        //Getters

        float getMinX() {
        return MinCoordinate.getX();
        }
        float getMinY() {
        return MinCoordinate.getY();
        }
        float getMaxX() {
        return MaxCoordinate.getX();;
        }
        float getMaxY() {
        return MaxCoordinate.getY();
        }
        vector<string> getColors(){
            return Colors;
        }
};

vector<SVGData> svgDataGenerator(){

}

vector<SVGData> svgDataSelecter(coordinate arrayCoordinate[], string arrayColors[]){

}

