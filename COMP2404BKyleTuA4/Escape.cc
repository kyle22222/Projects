#include <iostream>
using namespace std;
#include <string>
#include "Escape.h"

int main() {
  Escape game;
  game.runEscape();
  return 0;
}

Escape::Escape() {
  srand((unsigned)time(NULL));
  numSnorcs = 0;
  int timmyCol = random(10) + 7;
  int haroldCol;
  do {
    haroldCol = random(10) + 7;
  } while (haroldCol == timmyCol);

  hero1 = new Hero('T', MAX_ROW - 2, timmyCol, "Timmy");
  hero2 = new Hero('H', MAX_ROW - 2, haroldCol, "Harold");

  participants.add(hero1);
  participants.add(hero2);

  const char templateGrid[MAX_ROW+1][MAX_COL+1]={
      "-------------------------",
      "-             --        -",
      "-                      --",
      "-       --              -",
      "                  --    -",
      "--       -              -",
      "---                    --",
      "---       --          ---",
      "--                     --",
      "-            --        --",
      "---               --     ",
      "--        --    ---    --",
      "--  --                  -",
      "--        --       -     ",
      "--                  -    ",
      "--     --         --    -",
      "---                    --",
      "--       ---    --      -",
      "--                     --",
      "-------------------------"
  };

  pit = new Pit(templateGrid);
}

Escape::~Escape() {
  delete pit;
}

void Escape::runEscape() {
  while (!isOver()) {
    pit->print(participants, hero1, hero2);
    if (numSnorcs<=MAX_SNORCS && random(10)>0){
      spawnSnorc();
    }
    moveParticipants();

    for (int i = 0; i < participants.getSize(); i++) {
      Participant* participant = participants.get(i);
      Participant* collidedWith = checkForCollision(participant);
      if (collidedWith) {
        participant->incurDamage(collidedWith);
        collidedWith->incurDamage(participant);
      }
    }
  }

  pit->print(participants, hero1, hero2);
  printOutcome();
}

bool Escape::isOver() const {
  return (hero1->isSafe(pit) || hero1->isDead()) && (hero2->isSafe(pit) || hero2->isDead());
}

void Escape::spawnSnorc() {
  int row = random(5) + (MAX_ROW - 5); 
  int col = random(MAX_COL); 
  int strength = random(3) + 2; 

  Snorc* newSnorc = new Snorc(row, col, strength);
  participants.add(newSnorc);
  numSnorcs++;
}

Participant* Escape::checkForCollision(Participant* p) {
  for (int i = 0; i < participants.getSize(); i++) {
    Participant* other = participants.get(i);
    if (p != other && p->collide(other)) {
      return other;
    }
  }
  return nullptr;
}

void Escape::printOutcome() const {
  cout << "The escape is over!" << endl;
  if (hero1->isSafe(pit) && hero2->isSafe(pit)) {
    cout << "Both heroes have escaped." << endl;
  } else if (hero1->isDead() && hero2->isDead()) {
    cout << "Both heroes are dead." << endl;
  } else if (hero1->isSafe(pit)) {
    cout << hero1->getName() << " escaped, but " << hero2->getName() << " died." << endl;
  } else if (hero2->isSafe(pit)) {
    cout << hero2->getName() << " escaped, but " << hero1->getName() << " died." << endl;
  }
}

void Escape::moveParticipants() {
  for (int i = 0; i < participants.getSize(); i++) {
    Participant* current = participants.get(i);
    
    current->move(pit);
    
    Participant* collidedWith = checkForCollision(current);
    
    if (collidedWith) {
      current->incurDamage(collidedWith);
      collidedWith->incurDamage(current);
    }
  }
}
