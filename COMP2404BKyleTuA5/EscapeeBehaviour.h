#ifndef ESCAPEEBEHAVIOUR_H
#define ESCAPEEBEHAVIOUR_H
#include "MoveBehaviour.h"

class EscapeeBehaviour : public MoveBehaviour {
public:
    void move(int oldRow, int oldCol, int& newRow, int& newCol) override {
        newRow = oldRow + (random(5) - 2);
        newCol = oldCol + (random(3) - 1) ; 
    }
};

#endif
