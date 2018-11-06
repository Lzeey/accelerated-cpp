#include "Grad.h"

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include "grade.h"

// Default constructor
// Grad::Grade(); //Implicit

// Parsing constructor from input stream.
Grad::Grad(std::istream& is) {read(is);}

// Wrapper for grade function
// For graduate, grade is minimum of thesis or HW
double Grad::grade() const {
    return std::min(::grade(midterm, finals, homework), thesis);
}

std::istream& Grad::read(std::istream& is) {
    //Parser for reading in Grad from istream (name, midterm + finals + hw grades)
    //Expected format: <name> <midterm> <finals> <thesis> <bunch of HW scores>

    read_common(is);
    is >> thesis;
    //Parse HW score here
    read_hw(is, homework);

    //Compute grade
    if (valid())
        grd = grade();
    else
        grd = -1.;    // Invalid - HW not completed
    return is;
}
