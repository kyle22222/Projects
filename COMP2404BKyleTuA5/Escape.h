#ifndef ESCAPE_H
#define ESCAPE_H

#include "defs.h"
#include "List.h"
#include "Hero.h"
#include "Ninja.h"
#include "Snorc.h"

class Escape {
private:
    List<Participant*> participants;
    Hero* timmy;
    Hero* harold;
    int numSnorcs;

    bool isOver() const;
    static bool withinBounds(int row, int col);
    void spawnSnorc();
    void spawnNinja();
    Participant* checkForCollision(Participant* participant) const;
    void moveParticipants();
    void printPit() const;
    void printOutcome() const;

public:
    Escape();
    ~Escape();
    void runEscape();
};

#endif // ESCAPE_H
