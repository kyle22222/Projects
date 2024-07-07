#include <iostream>
#include "CourseArray.h"
using namespace std;

CourseArray::CourseArray() : size(0) {}

CourseArray::~CourseArray() {
    for (int i = 0; i < size; ++i) {
        delete elements[i];
    }
}

void CourseArray::add(Course* c) {
    if (size >= MAX_ARR){
        return;
    }

    int i;
    for (i = size - 1; (i >= 0) && elements[i]->lessThan(*c); --i) {
        elements[i + 1] = elements[i];
    }
    elements[i + 1] = c;
    ++size;
}

bool CourseArray::find(int id, Course** c) {
    for (int i = 0; i < size; ++i) {
        if (elements[i]->getCourseId() == id) {
            *c = elements[i];
            return true;
        }
    }
    *c = nullptr;
    return false;
}

void CourseArray::print() const {
    cout << endl << "COURSES:" << endl;
    for (int i = 0; i < size; ++i) {
        elements[i]->print();
    }
}

void CourseArray::print(const string& term) const {
    cout << endl << "COURSES in " << term << ":" << endl;
    for (int i = 0; i < size; ++i) {
        if (elements[i]->getTerm() == term) {
            elements[i]->print();
        }
    }
}
