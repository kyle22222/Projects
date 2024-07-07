#ifndef STUARRAY_H
#define STUARRAY_H

#include "Student.h"
#include "defs.h"

class StuArray {
public:
    StuArray();
    ~StuArray();
    void add(Student*);
    bool find(string num, Student** stu);
    void print() const;

private:
    Student* elements[MAX_ARR];
    int size;
};

#endif
