#ifndef STUDENT_H
#define STUDENT_H

#include <string>

using namespace std;

class Student {
private:
    string number;
    string name;
    string majorPgm;

public:
    Student(const string& num, const string& nam, const string& maj);
    bool lessThan(const Student& stu) const;
    void print() const;
    string getNumber() const;
    string getName() const;
};

#endif // STUDENT_H
