#ifndef RESCUEDBEHAVIOUR_H
#define RESCUEDBEHAVIOUR_H

#include "MoveBehaviour.h"

class RescuedBehaviour : public MoveBehaviour {
public:
    void move(int oldRow, int oldCol, int& newRow, int& newCol) override {
        newRow = oldRow - 1;
        newCol = oldCol;
    }
};

#endif
