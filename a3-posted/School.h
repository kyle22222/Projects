#ifndef SCHOOL_H
#define SCHOOL_H

#include <string>
#include "StuArray.h"
#include "CourseArray.h"
#include "RegList.h"

using namespace std;

class School {
private:
    string name;
    static StuArray students;
    static CourseArray courses;
    static RegList registrations;

public:
    School(const string& name);
    ~School();
    
    void addStu(Student* stu);
    void addCourse(Course* cou);
    void addRegistration(Student* stu, Course* cou);
    
    bool findStudent(const string& num, Student** stu);
    bool findCourse(int id, Course** cou);
    
    void printStudents() const;
    void printCourses() const;
    void printCourseByTerm(const string& term) const;
    void printRegistrations() const;
    void printRegistrationsByStu(Student* stu) const;
};

#endif 
