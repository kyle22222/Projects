#ifndef VILLAINBEHAVIOUR_H
#define VILLAINBEHAVIOUR_H
#include "MoveBehaviour.h"
#include "defs.h"

class VillainBehaviour : public MoveBehaviour {
public:
    void move(int oldRow, int oldCol, int& newRow, int& newCol) override {
        int potentialNewRow = oldRow + (random(3) - 1); 
        newRow = (potentialNewRow > (MAX_ROW - 7)) ? oldRow : potentialNewRow;
        newCol = oldCol + (random(3) - 1);
    }
};

#endif
