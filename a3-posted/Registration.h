#ifndef REGISTRATION_H
#define REGISTRATION_H

#include "Student.h"
#include "Course.h"
#include "defs.h"
#include <iomanip>

using namespace std;

class Registration {
private:
    static int nextId;
    int id;
    Student* student;
    Course* course;

public:
    Registration(Student* stu, Course* cou);
    Student* getStudent() const;
    bool lessThan(const Registration& other) const;
    void print() const;
};

#endif // REGISTRATION_H
