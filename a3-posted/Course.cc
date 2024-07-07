#include "Course.h"

int Course::nextId = COURSE_ID;

Course::Course(const string& term, const string& subject, int code, char section, const string& instructor) 
    : term(term), subject(subject), code(code), section(section), instructor(instructor) {
    id = nextId++;
}

bool Course::lessThan(const Course& other) const {
    if (term != other.term)
        return term < other.term;
    if (subject != other.subject)
        return subject < other.subject;
    if (code != other.code)
        return code < other.code;
    return section < other.section;
}

void Course::print() const {
    cout<< id <<"  Term: " << term << "  " << subject << " " << code << " " << section <<"  Instr: " << instructor << endl;
}

int Course::getCourseId() const {
    return id;
}

string Course::getTerm() const {
    return term;
}

string Course::getCourseCode() const {
    return subject + " " + to_string(code) + "-" + string(1, section);
}
