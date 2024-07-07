#include "Student.h"
#include <iomanip>
#include <iostream>

Student::Student(const string& num, const string& nam, const string& maj) : number(num), name(nam), majorPgm(maj) {}

bool Student::lessThan(const Student& stu) const {
    return name < stu.name;
}

void Student::print() const {
    cout << left << setw(10) << number << " " << setw(10) << name << majorPgm << endl;
}

string Student::getNumber() const {
    return number;
}

string Student::getName() const {
    return name;
}
