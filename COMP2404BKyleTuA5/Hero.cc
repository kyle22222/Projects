#include "Hero.h"
#include "defs.h"
#include "EscapeeBehaviour.h"
#include "RescuedBehaviour.h"

Hero::Hero(char av, int r, int c, const string& n)
    : Participant(av, r, c, new EscapeeBehaviour()),
      name(n), health(MAX_HEALTH), rescued(false) {}

void Hero::incurDamage(Participant* other) {
    int damage = other->causeDamage();
    if (damage == RESCUE) {
        rescued = true;
        moveBehaviour = new RescuedBehaviour();
    } else {
        health -= damage;
        if (health <= 0) {
            dead = true;
            avatar = '+';
        }
    }
}

int Hero::causeDamage() const {
    return 0;
}

bool Hero::isSafe() const {
    return row == 0;
}