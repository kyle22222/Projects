#include "Ninja.h"
#include "RescuerBehaviour.h"
#include "RescuedBehaviour.h"
#include "VillainBehaviour.h"

Ninja::Ninja(int r, int c)
    : Participant('N', r, c, new RescuerBehaviour()),
      strength(0), poisoned(false) {}

void Ninja::incurDamage(Participant* other) {
    if (poisoned) return;

    int damage = other->causeDamage();

    if (damage == RESCUE) {
    } else if (damage == 0) {

        moveBehaviour = new RescuedBehaviour();
    } else {
        poisoned = true;
        avatar = 'S';
        strength = 6 + random(3); 
        moveBehaviour = new VillainBehaviour();
    }
}

int Ninja::causeDamage() const {
    return poisoned ? strength : RESCUE;
}

bool Ninja::isSafe() const {
    return row == 0 || row == 21;
}
