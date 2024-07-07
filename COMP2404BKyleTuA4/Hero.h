#ifndef HERO_H
#define HERO_H

#include "Participant.h"
#include <string>

class Hero : public Participant {
public:
    Hero(char avatar, int row, int col, string name);
    virtual ~Hero() override {}

    virtual void move(Pit* pit) override;
    virtual void incurDamage(Participant* other) override;
    virtual int causeDamage() override;

    string getName() const;
    int getHealth() const;
    virtual bool isSafe(const Pit* pit) const override;

private:
    string name;
    int health;
};

#endif 
