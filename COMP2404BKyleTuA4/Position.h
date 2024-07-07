#ifndef POSITION_H
#define POSITION_H
#include "defs.h"

class Position {
public:
    Position(int row, int col);
    void set(int row, int col);
    bool equals(const Position& other) const;

    int getRow() const;
    int getCol() const;
    void setRow(int r);
    void setCol(int c);

private:
    int row;
    int col;

    void validate();
};

#endif
