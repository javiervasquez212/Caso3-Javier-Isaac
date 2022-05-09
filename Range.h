#ifndef _RANGE_
#define _RANGE_ 0

class Range{

    private:
        int start;
        int end;

    public:
        //Setters

        void setStart(int pStart) {
        start = pStart;
        }
        void setEnd(int pEnd) {
        end = pEnd;
        }

        //Getters

        int getStart() {
        return start;
        }
        int getEnd() {
        return end;
        }
};

#endif