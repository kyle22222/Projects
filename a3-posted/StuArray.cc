#include <iostream>
#include "StuArray.h"
using namespace std;

StuArray::StuArray() : size(0) {}

StuArray::~StuArray() {
    for (int i = 0; i < size; ++i) {
        delete elements[i];
    }
}

void StuArray::add(Student* stu) {
    if (size >= MAX_ARR){
        return;
    }

    int i;
    for (i = size - 1; (i >= 0) && elements[i]->lessThan(*stu); --i) {
        elements[i + 1] = elements[i];
    }
    elements[i + 1] = stu;
    ++size;
}

bool StuArray::find(string num, Student** stu) {
    for (int i = 0; i < size; ++i) {
        if (elements[i]->getNumber() == num) {
            *stu = elements[i];
            return true;
        }
    }
    *stu = nullptr;
    return false;
}

void StuArray::print() const {
    cout << endl << "STUDENTS:" << endl;
    for (int i = 0; i < size; ++i) {
        elements[i]->print();
    }
}
