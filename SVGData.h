
#ifndef _SVGDATA_
#define _SVGDATA_ 0

#include "Coordinate.h"
#include "Range.h"

class SVGData{

    private:
        coordinate MinCoordinate;
        coordinate MaxCoordinate;
        Range Colors;

    public:

        //Constructor

        SVGData(coordinate pMin, coordinate pMax, Range pColors){
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
        void setColors(Range pColors){
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
        Range getColors(){
            return Colors;
        }
};

#endif