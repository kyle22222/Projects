#include "Escape.h"
#include "EscapeeBehaviour.h"
#include "RescuerBehaviour.h"
#include "VillainBehaviour.h"
#include "RescuedBehaviour.h"
#include <cstdlib>
#include <ctime>

int main() {
    Escape game;
    game.runEscape();
    return 0;
}

Escape::Escape() {
    srand((unsigned)time(NULL)); // Seed the PRNG

    int colTimmy = random(10) + 7;
    int colHarold;
    do {
        colHarold = random(10) + 7;
    } while (colHarold == colTimmy);
    
    timmy = new Hero('T', MAX_ROW, colTimmy, "Timmy");
    harold = new Hero('H', MAX_ROW, colHarold, "Harold");
    
    participants += timmy;
    participants += harold;

    numSnorcs = 0;
}

Escape::~Escape() {
}

void Escape::runEscape() {
    while (!isOver()) {
        if (random(100) < SNORC_SPAWN && numSnorcs < MAX_SNORCS) {
            spawnSnorc();
        }
        if (random(100) < NINJA_SPAWN) {
            spawnNinja();
        }
        moveParticipants();
        printPit();
    }
    printOutcome();
}

bool Escape::isOver() const {
    return ((timmy->isSafe()||timmy->isDead()) && (harold->isSafe()||harold->isDead())); //
}

bool Escape::withinBounds(int row, int col) {
    return (row >= 0 && row <= MAX_ROW) && (col > 0 && col <= MAX_COL);
}

void Escape::spawnSnorc() {
    int row = 16 + random(5);
    int col = random(MAX_COL) + 1;
    int strength = random(3) + 2; 
    Snorc* snorc = new Snorc(row, col, strength);
    participants += snorc;
    numSnorcs++;
}

void Escape::spawnNinja() {
    int col = random(MAX_COL) + 1;
    Ninja* ninja = new Ninja(0, col);
    participants += ninja;
}

Participant* Escape::checkForCollision(Participant* participant) const {
    Participant* arr[MAX_ARR];
    int size;
    participants.convertToArray(arr, size);
    for (int i = 0; i < size; ++i) {
        if (arr[i] != participant && arr[i]->getRow() == participant->getRow() && arr[i]->getCol() == participant->getCol()) {
            return arr[i];
        }
    }
    return nullptr;
}

void Escape::moveParticipants() {
    Participant* arr[MAX_ARR];
    int size;
    participants.convertToArray(arr, size);
    for (int i = 0; i < size; ++i) {
        if (!arr[i]->isDead() && !arr[i]->isSafe()) {
            int oldRow = arr[i]->getRow();
            int oldCol = arr[i]->getCol();

            int newRow, newCol;
            arr[i]->moveBehaviour->move(oldRow, oldCol, newRow, newCol);

            if (withinBounds(newRow, newCol)) {
                arr[i]->updatePosition(newRow, newCol);
            }

            Participant* collidedParticipant = checkForCollision(arr[i]);
            if (collidedParticipant && !collidedParticipant->isDead() && !collidedParticipant->isSafe()) {
                arr[i]->incurDamage(collidedParticipant);
                collidedParticipant->incurDamage(arr[i]);
            }
        }
    }
}


void Escape::printPit() const {
    char pit[MAX_ROW + 2][MAX_COL + 3] = {
        "---------------------------",
        "|                         |",
        "|                         |",
        "|                         |",
        "|                         |",
        "|                         |",
        "|                         |",
        "|                         |",
        "|                         |",
        "|                         |",
        "|                         |",
        "|                         |",
        "|                         |",
        "|                         |",
        "|                         |",
        "|                         |",
        "|                         |",
        "|                         |",
        "|                         |",
        "|                         |",
        "|                         |",
        "---------------------------"
    };

    Participant* arr[MAX_ARR];
    int size;
    participants.convertToArray(arr, size);
    for (int i = 0; i < size; ++i) {
        if (!arr[i]->isDead() && withinBounds(arr[i]->getRow(), arr[i]->getCol())) {
            pit[arr[i]->getRow() + 1][arr[i]->getCol() + 1] = arr[i]->getAvatar();
        }
    }

    for (int i = 0; i < MAX_ROW + 2; ++i) {
        cout.write(pit[i], MAX_COL + 2);
        cout << endl;
    }

    cout << timmy->getName() << ": Health=" << timmy->getHealth();
    if (timmy->isSafe()) cout << " (Escaped)";
    cout << endl;

    cout << harold->getName() << ": Health=" << harold->getHealth();
    if (harold->isSafe()) cout << " (Escaped)";
    cout << endl;
}


void Escape::printOutcome() const {
    cout << timmy->getName();
    if (timmy->isDead()) {
        cout << " died.";
    } else if (timmy->isSafe()) {
        if (timmy->isRescued()) {
            cout << " was rescued.";
        } else {
            cout << " escaped on their own.";
        }
    }
    cout << endl;

    cout << harold->getName();
    if (harold->isDead()) {
        cout << " died.";
    } else if (harold->isSafe()) {
        if (harold->isRescued()) {
            cout << " was rescued.";
        } else {
            cout << " escaped on their own.";
        }
    }
    cout << endl;
}