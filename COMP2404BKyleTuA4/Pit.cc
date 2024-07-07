#include "Pit.h"
#include "PartArray.h"
#include "Hero.h"
#include <cstring>
#include <iostream>

using namespace std;

Pit::Pit(const char sourceLayout[MAX_ROW+1][MAX_COL+1]) {
    memcpy(layout, sourceLayout, sizeof(layout));
}

bool Pit::validPos(int row, int col) const {
    return withinBounds(row, col) && layout[row][col] == ' ';
}

bool Pit::withinBounds(int row, int col) const {
    return row >= 0 && row <= MAX_ROW && col >= 0 && col < MAX_COL;
}

bool Pit::underLedge(const Position* p) const {
    if (!p) return false;
    int row = p->getRow();
    int col = p->getCol();
    return layout[row+1][col] == '-';
}

void Pit::print(const PartArray& participants, const Hero* h1, const Hero* h2) const {
    char display[MAX_ROW+1][MAX_COL+1];
    memcpy(display, layout, sizeof(layout));

    for (int i = 0; i < participants.getSize(); ++i) {
        Participant* p = participants.get(i);
        if (p) {
            display[p->getRow()][p->getCol()] = p->getAvatar();
        }
    }

    for (int i = 0; i < MAX_ROW; ++i) {
        cout << display[i] << endl;
    }

    if (h1) cout << h1->getName() << ": " << h1->getHealth() << endl;
    if (h2) cout << h2->getName() << ": " << h2->getHealth() << endl;
}