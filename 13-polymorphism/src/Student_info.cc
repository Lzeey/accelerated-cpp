#include "Student_info.h" //Defines Student_info struct

#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

#include "Core.h"
#include "Grad.h"
#include "grade.h"

bool compare(Student_info& a, Student_info& b) {
    //Compares two objects of Student_info by name
    return a.name() < b.name();
};

//Copy constructor
Student_info::Student_info(const Student_info& s) {
    if (s.cp) {
        student_type = s.student_type;
        cp = s.cp->clone();
    }
}

//Assignment constructor using copy-swap idiom
Student_info& Student_info::operator=(Student_info s) {
    //(Try to implement swap rather than this?)
    swap(*this, s);
    return *this;
}

void swap(Student_info& s1, Student_info& s2) {
    using std::swap;

    swap(s1.cp, s2.cp);
}
// Wrapper for grade function
// double Student_info::grade() const {
//     return ::grade(midterm, finals, homework);
// }

std::istream& Student_info::read(std::istream& is) {
    //Parser for reading in Student_info from istream (name, midterm + finals + hw grades)
    //Expected format: <type> <name> <midterm> <finals> <bunch of HW scores>
    delete cp;
    char ch;
    is >> ch;
    if (ch == 'U') {
        student_type = "U";
        cp = new Core(is);
    } else {
        student_type = "G";
        cp = new Grad(is);
    }

    return is;
}
