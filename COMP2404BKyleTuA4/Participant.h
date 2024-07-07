#ifndef PARTICIPANT_H
#define PARTICIPANT_H

#include "Position.h"
#include "Pit.h"

class Participant {
protected:
    char avatar;
    bool dead;
    Position* position;

public:
    Participant(char avatar, int row, int col);
    virtual ~Participant();

    virtual void move(Pit* p) = 0;
    virtual void incurDamage(Participant* p) = 0;
    virtual int causeDamage() = 0;
    virtual bool isSafe(const Pit* p) const = 0;

    bool collide(const Participant* p) const;

    char getAvatar() const;
    int getRow() const;
    int getCol() const;
    bool isDead() const;
};

#endif
