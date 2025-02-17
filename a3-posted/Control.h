#ifndef CONTROL_H
#define CONTROL_H

#include "School.h"
#include "View.h"

class Control
{
  public:
    Control(const string& schoolName);
    ~Control();
    void launch();
    void initStudents(School* sch);
    void initCourses(School* sch);

  private:
    School* school;
    View view;
};

#endif
