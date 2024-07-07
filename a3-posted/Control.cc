#include <iostream>
using namespace std;
#include <string>
#include "Control.h"

int main() {
  Control control("Carleton University");
  control.launch();
  
  return 0;
}

Control::Control(const std::string& schoolName) {
  school = new School(schoolName);
}

Control::~Control() {
  delete school;
}

void Control::launch() {
  initStudents(school);
  initCourses(school);
  int AdminChoice;

  do {
    view.showAdminMenu(AdminChoice);

    switch (AdminChoice) {
      case 1:
        school->printStudents();
        break;
      case 2:
        school->printCourses();
        break;
      case 3:
        school->printRegistrations();
        break;
      case 4:{
        string studentNum;
        Student* student;

        do {
          cout << "Enter Student Number: ";
          view.readStr(studentNum);
          if (!school->findStudent(studentNum, &student)) {
            view.printStr("Invalid student number. Please try again.\n");
          }
        } while (!school->findStudent(studentNum, &student));

        int studentChoice;
        do {
          view.showStudentMenu(student->getName(), studentChoice);
          switch (studentChoice) {
              case 1:{
                string term;
                cout << "Enter a Term: ";
                view.readStr(term);
                school->printCourseByTerm(term);
                break;
              }

              case 2:
                school->printRegistrationsByStu(student);
                break;

              case 3:{
                int courseId;
                Course* course;
                cout << "Enter Course ID: ";
                view.readInt(courseId);
                if (!school->findCourse(courseId, &course)) {
                  view.printStr("Invalid course ID. Please try again.\n");
                } else {
                  school->addRegistration(student, course);
                }
                break;
              }
          }
        } while (studentChoice != 0);
        break;
      }
    }
  } while (AdminChoice != 0);
}

void Control::initStudents(School* sch)
{
  sch->addStu(new Student("100567888", "Matilda", "CS"));
  sch->addStu(new Student("100333444", "Harold", "Geography"));
  sch->addStu(new Student("100444555", "Joe", "Physics"));
  sch->addStu(new Student("100775588", "Timmy", "CS"));
  sch->addStu(new Student("100111222", "Amy", "Math"));
  sch->addStu(new Student("100222333", "Stanley", "Art History"));
}

void Control::initCourses(School* sch)
{
  sch->addCourse(new Course("F23", "COMP", 2401, 'A', "Laurendeau"));
  sch->addCourse(new Course("F23", "COMP", 2401, 'B', "Hillen"));
  sch->addCourse(new Course("F23", "COMP", 2401, 'C', "Laurendeau"));
  sch->addCourse(new Course("F23", "COMP", 2401, 'D', "Hillen"));
  sch->addCourse(new Course("F23", "COMP", 2402, 'A', "Shaikhet"));
  sch->addCourse(new Course("F23", "COMP", 2402, 'B', "Shaikhet"));
  sch->addCourse(new Course("F23", "COMP", 2404, 'A', "Hill"));
  sch->addCourse(new Course("F23", "COMP", 2404, 'B', "Hill"));
  sch->addCourse(new Course("F23", "COMP", 2406, 'A', "Nel"));
  sch->addCourse(new Course("F23", "COMP", 2406, 'B', "Shaikhet"));
  sch->addCourse(new Course("F23", "COMP", 2804, 'A', "Morin"));
  sch->addCourse(new Course("F23", "COMP", 2804, 'B', "Hill"));

  sch->addCourse(new Course("W24", "COMP", 2401, 'A', "CI"));
  sch->addCourse(new Course("W24", "COMP", 2401, 'B', "Lanthier"));
  sch->addCourse(new Course("W24", "COMP", 2402, 'A', "Sharp"));
  sch->addCourse(new Course("W24", "COMP", 2402, 'B', "Sharp"));
  sch->addCourse(new Course("W24", "COMP", 2404, 'A', "Hill"));
  sch->addCourse(new Course("W24", "COMP", 2404, 'B', "Laurendeau"));
  sch->addCourse(new Course("W24", "COMP", 2404, 'C', "Laurendeau"));
  sch->addCourse(new Course("W24", "COMP", 2406, 'A', "Nel"));
  sch->addCourse(new Course("W24", "COMP", 2406, 'B', "Nel"));
  sch->addCourse(new Course("W24", "COMP", 2804, 'A', "Hill"));
  sch->addCourse(new Course("W24", "COMP", 2804, 'B', "Hill"));
}


