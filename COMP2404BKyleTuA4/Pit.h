#ifndef PIT_H
#define PIT_H

#include "Position.h"
class PartArray;
class Hero;

class Pit {
public:
    Pit(const char sourceLayout[MAX_ROW+1][MAX_COL+1]);
    bool validPos(int row, int col) const;
    bool withinBounds(int row, int col) const;
    bool underLedge(const Position* p) const;
    void print(const PartArray& participants, const Hero* h1, const Hero* h2) const;

private:
    char layout[MAX_ROW+1][MAX_COL+1];
};

#endif
