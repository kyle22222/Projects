#include "Snorc.h"
#include "VillainBehaviour.h"

Snorc::Snorc(int r, int c, int str)
    : Participant('s', r, c, new VillainBehaviour()),
      strength(str) {}

void Snorc::incurDamage(Participant* other) {
}

int Snorc::causeDamage() const {
    return strength;
}

bool Snorc::isSafe() const {
    return false;
}
