#include "Position.h"

Position::Position(int row, int col) : row(row), col(col) {
    validate();
}

void Position::set(int row, int col){
    this->row = row;
    this->col = col;
    validate();
}

bool Position::equals(const Position& other) const {
    return (row == other.row) && (col == other.col);
}

int Position::getRow() const {
    return row;
}

int Position::getCol() const {
    return col;
}

void Position::setRow(int r){
    row=r;
}

void Position::setCol(int c){
    col=c;
}

void Position::validate() {
    if (row < 0) row = 0;
    else if (row >= MAX_ROW) row = MAX_ROW - 1;
    
    if (col < 0) col = 0;
    else if (col >= MAX_COL) col = MAX_COL - 1;
}