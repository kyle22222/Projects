#include "Participant.h"

Participant::Participant(char av, int row, int col) : avatar(av), dead(false) {
    position = new Position(row, col);
}

Participant::~Participant() {
    delete position;
}

bool Participant::collide(const Participant* other) const {
    return position->equals(*other->position);
}

char Participant::getAvatar() const {
    return avatar;
}

int Participant::getRow() const {
    return position->getRow();
}

int Participant::getCol() const {
    return position->getCol();
}

bool Participant::isDead() const {
    return dead;
}
