#ifndef PARTARRAY_H
#define PARTARRAY_H

#include "Participant.h"

class PartArray {
public:
    PartArray();
    ~PartArray();
    void add(Participant* p);
    Participant* get(int index) const;
    int getSize() const;

private:
    Participant* elements[MAX_ARR];
    int size;
};

#endif
