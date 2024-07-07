#ifndef SNORC_H
#define SNORC_H

#include "Participant.h"

class Snorc : public Participant {
public:
    Snorc(int row, int col, int strength);
    virtual ~Snorc() {}

    virtual void move(Pit* pit) override;
    virtual void incurDamage(Participant* other) override;
    virtual int causeDamage() override;
    virtual bool isSafe(const Pit* pit) const override { return false; }

private:
    int strength;
};

#endif // SNORC_H
