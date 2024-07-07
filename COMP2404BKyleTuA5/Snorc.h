#ifndef SNORC_H
#define SNORC_H

#include "Participant.h"

class Snorc : public Participant {
private:
    int strength;

public:
    Snorc(int row, int col, int str);

    void incurDamage(Participant* other) override; 
    int causeDamage() const override; 
    bool isSafe() const override;
};

#endif
