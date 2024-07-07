#include "School.h"
#include <iostream>

StuArray School::students;
CourseArray School::courses;
RegList School::registrations;

School::School(const string& name) : name(name) {}

School::~School() {
    registrations.cleanData();
}

void School::addStu(Student* stu) {
    students.add(stu);
}

void School::addCourse(Course* cou) {
    courses.add(cou);
}

void School::addRegistration(Student* stu, Course* cou) {
    Registration* reg = new Registration(stu, cou);
    registrations.add(reg);
}

bool School::findStudent(const string& num, Student** stu) {
    return students.find(num, stu);
}

bool School::findCourse(int id, Course** cou) {
    return courses.find(id, cou);
}

void School::printStudents() const {
    cout << name << endl;
    students.print();
}

void School::printCourses() const {
    cout << name << endl;
    courses.print();
}

void School::printCourseByTerm(const string& term) const {
    cout << name << " - " << term << endl;
    courses.print(term);
}

void School::printRegistrations() const {
    cout << name << endl;
    registrations.print();
}

void School::printRegistrationsByStu(Student* stu) const {
    cout << name << " - " << stu->getName() << endl;
    RegList localRegistrations(registrations, stu);
    localRegistrations.print();
}
