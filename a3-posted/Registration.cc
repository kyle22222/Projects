#include "Registration.h"

int Registration::nextId = REG_ID;

Registration::Registration(Student* stu, Course* cou)
    : student(stu), course(cou), id(nextId++) {}

Student* Registration::getStudent() const {
    return student;
}

bool Registration::lessThan(const Registration& other) const {
    return course->lessThan(*other.course);
}

void Registration::print() const {
    cout<< left << setw(6) << id << left << setw(10) << student->getName() << left << setw(6) 
    << course->getTerm() << left << setw(10) << course->getCourseCode() << endl;
}
