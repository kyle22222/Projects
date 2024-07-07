#ifndef ESCAPE_H
#define ESCAPE_H

#include "PartArray.h"
#include "Pit.h"
#include "Hero.h"
#include "Snorc.h"

class Escape {
private:
  int numSnorcs;
  PartArray participants;
  Pit* pit;
  Hero* hero1;
  Hero* hero2;
  void spawnSnorc();
  void moveParticipants();
  Participant* checkForCollision(Participant* p);
  bool isOver() const;
  void printOutcome() const;

public:
  Escape();
  ~Escape();
  void runEscape();

};

#endif
