
#ifndef _COORDINATE_
#define _COORDINATE_ 0

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

#endif