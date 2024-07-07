#ifndef NINJA_H
#define NINJA_H

#include "defs.h"
#include "Participant.h"

class Ninja : public Participant {
private:
    int strength;
    bool poisoned;

public:
    Ninja(int row, int col);

    void incurDamage(Participant* other) override;
    int causeDamage() const override;
    bool isSafe() const override;
};

#endif // NINJA_H
