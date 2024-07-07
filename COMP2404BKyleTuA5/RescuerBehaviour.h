#ifndef RESCUERBEHAVIOUR_H
#define RESCUERBEHAVIOUR_H

#include "MoveBehaviour.h"

class RescuerBehaviour : public MoveBehaviour {
public:
    void move(int oldRow, int oldCol, int& newRow, int& newCol) override {
        newRow = oldRow + 1;
        newCol = oldCol;
    }
};

#endif
