#include <vector>
#include <string>
#include <iostream>
#include "grade.h"
#include "Student_info.h" //Defines Student_info struct

bool compare(Student_info& a, Student_info& b) {
    //Compares two objects of Student_info by name
    return a.name() < b.name();
};

// Default constructor
Student_info::Student_info(): midterm(0), finals(0) {}

// Parsing constructor from input stream.
Student_info::Student_info(std::istream& is) {read(is);}

// Wrapper for grade function
// double Student_info::grade() const {
//     return ::grade(midterm, finals, homework);
// }

// Wrapper for checking if student failed course
double Student_info::failed() const {
    return ::failgrade(grade());

}

std::istream& Student_info::read(std::istream& is) {
    //Parser for reading in Student_info from istream (name, midterm + finals + hw grades)
    //Expected format: <name> <midterm> <finals> <bunch of HW scores>

    is >> n >> midterm >> finals;

    //Parse HW score here
    read_hw(is, homework);

    //Compute grade
    if (valid())
        grd = ::grade(midterm, finals, homework);
    else
        grd = -1.;    // Invalid - HW not completed
    return is;
}

std::istream& Student_info::read_hw(std::istream& is, std::vector<double>& hw) {
    //Parser for reading in HW score for istream
    
    if (is) { //Ensure that there is something in the stream
        hw.clear(); //TODO: WHY THIS? Cause we don't know what is being passed into the function 
        // And the user may throw a reference to a vector that contains the previous record (which in this case is true)
        double x;

        // This is actually a hack. We are forcing istream to reach an error state
        // as our record begins with a string. In general, we should try to parse for end of record.
        while (is >> x) {
            hw.push_back(x);
        }

        //Clear input stream to read input for next student (we are assuming read_hw returns an error state)
        //Note that istream.clear() only occurs if cin is NOT in an error state to begin with 
        is.clear(); //TODO: WHY THIS?
    }

    return is;
}