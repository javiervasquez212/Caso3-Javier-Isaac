#ifndef _RANGE_
#define _RANGE_ 0

class Range{

    private:
        int Start;
        int End;

    public:
        //Setters

        void setStart(int pStart) {
        Start = pStart;
        }
        void setEnd(int pEnd) {
        End = pEnd;
        }

        //Getters

        int getStart() {
        return Start;
        }
        int getEnd() {
        return End;
        }
};

#endif