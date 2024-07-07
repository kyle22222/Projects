#include "Hero.h"

Hero::Hero(char avatar, int row, int col, string name)
: Participant(avatar, row, col), name(name), health(MAX_HEALTH) {}

void Hero::move(Pit* pit) {
    if (isDead() || isSafe(pit)) return;

    if (pit->underLedge(position)) {
        int colChange = random(2);
        if (colChange==0){
            colChange = getCol() + 1;
        } else {
            colChange = getCol() - 1;
        }
        if (pit->validPos(getRow(), colChange)) {
            position->setCol(colChange);
        }
    } else {
        int move = random(100);

        if (move < 50) { 
            position->setRow(max(getRow() - 1, 0));

        } else if (move < 60) {
            position->setRow(max(getRow() - 2, 0));

        } else { 
            position->setRow(min(getRow() + 1, MAX_ROW)); 
        }

        int colChange = random(5) - 2;
        int newCol = getCol() + colChange;
        if (pit->validPos(getRow(), newCol)) {
            position->setCol(newCol);
        }
    }
}

void Hero::incurDamage(Participant* other) {
    if (other == nullptr) return;
    health -= other->causeDamage();
    if (health <= 0) {
        health = 0;
        avatar = '+';
        dead = true;
    }
}

int Hero::causeDamage() {
    return 0; 
}

bool Hero::isSafe(const Pit* pit) const {
    return position->getRow() == 0; 
}

string Hero::getName() const {
    return name;
}

int Hero::getHealth() const {
    return health;
}
