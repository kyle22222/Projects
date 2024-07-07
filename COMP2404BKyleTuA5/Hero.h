#ifndef HERO_H
#define HERO_H

#include "Participant.h"
#include <string>

class Hero : public Participant {
private:
    string name;
    int health;
    bool rescued;

public:
    Hero(char avatar, int row, int col, const string& name);

    void incurDamage(Participant* other) override;
    int causeDamage() const override;
    bool isSafe() const override;

    string getName() const { return name; }
    int getHealth() const { return health; }
    bool isRescued() const { return rescued; }
};

#endif
