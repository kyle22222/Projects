#ifndef COURSE_H
#define COURSE_H

#include <iostream>
#include <string>
#include "defs.h"

using namespace std;

class Course {
private:
    static int nextId;
    int id;
    string term;
    string subject;
    int code;
    char section;
    string instructor;

public:
    Course(const string& term, const string& subject, int code, char section, const string& instructor);
    bool lessThan(const Course& other) const;
    void print() const;
    int getCourseId() const;
    string getTerm() const;
    string getCourseCode() const;
};

#endif
