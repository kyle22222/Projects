#ifndef PARTICIPANT_H
#define PARTICIPANT_H

#include "MoveBehaviour.h"
using namespace std;

class Participant {
protected:
    char avatar;
    bool dead;
    int row, col;

public:
    MoveBehaviour* moveBehaviour;

    Participant(char av, int r, int c, MoveBehaviour* mb);
    virtual ~Participant();

    virtual void incurDamage(Participant* other) = 0;
    virtual int causeDamage() const = 0;
    virtual bool isSafe() const = 0;

    char getAvatar() const { return avatar; }
    int getRow() const { return row; }
    int getCol() const { return col; }
    bool isDead() const { return dead; }

    void setMoveBehaviour(MoveBehaviour* newBehaviour);
    void move();

    void updatePosition(int newRow, int newCol);
};

#endif