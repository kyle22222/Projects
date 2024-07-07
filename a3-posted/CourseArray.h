#ifndef COURSEARRAY_H
#define COURSEARRAY_H

#include "Course.h"

class CourseArray {
public:
    CourseArray();
    ~CourseArray();
    void add(Course*);
    bool find(int id, Course** c);
    void print() const;
    void print(const string& term) const;

private:
    Course* elements[MAX_ARR];
    int size;
};

#endif
