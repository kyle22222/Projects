#ifndef REGLIST_H
#define REGLIST_H

#include "Registration.h"

class RegList {

    class Node {
    public:
        Registration* data;
        Node* next;
    };

public:
    RegList();
    RegList(RegList& otherList, Student* stu);
    ~RegList();
    void add(Registration* r);
    void cleanData();
    void print() const;

private:
    Node* head;
    Node* tail;
};

#endif
