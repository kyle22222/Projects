#include "Snorc.h"
#include "Pit.h"

Snorc::Snorc(int row, int col, int str)
: Participant('s', row, col), strength(str) {}

void Snorc::move(Pit* pit) {
    if (isDead()) return;

    int newRow;
    if (random(2)==0){
        newRow = getRow() + 1;
    } else {
        newRow = getRow() - 1;
    }
    int newCol = getCol() + random(3) - 1;

    if (newRow < MAX_ROW - 7) {
        newRow = getRow();
    }

    if (pit->withinBounds(newRow, newCol)) {
        position->setRow(newRow);
        position->setCol(newCol);
    }
}

void Snorc::incurDamage(Participant* other) {
}

int Snorc::causeDamage() {
    return strength;
}

bool isSafe(const Pit* pit) {
    return false; 
}