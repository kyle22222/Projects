#include "Participant.h"

Participant::Participant(char av, int r, int c, MoveBehaviour* mb)
    : avatar(av), dead(false), row(r), col(c), moveBehaviour(mb) {}

Participant::~Participant() {
    delete moveBehaviour;
}

void Participant::move() {
    moveBehaviour->move(row, col, row, col);
}

void Participant::setMoveBehaviour(MoveBehaviour* newBehaviour) {
    if (moveBehaviour != newBehaviour) {
        delete moveBehaviour;
        moveBehaviour = newBehaviour;
    }
}

void Participant::updatePosition(int newRow, int newCol) {
    this->row = newRow;
    this->col = newCol;
}
