#include <vector>
#include <stdexcept>
#include "median.h" //Median score
#include "Student_info.h"


double grade(const double& midterm, const double& finals, const double& hw) { 
    // See guide for Google
    // All input parameters should be either value OR const references (NOT pointers)
    // https://google.github.io/styleguide/cppguide.html#Reference_Arguments
    return 0.4*midterm + 0.4*finals + 0.2*hw;
}

double grade(const double& midterm, const double& finals, const std::vector<double>& hw) {
    //Wrapper for computing student's grade from homework vector
    if (hw.size() == 0) 
        throw std::domain_error("Student has no homework score");
    return grade(midterm, finals, median(hw));
}

double grade(const Student_info& s) {

    //Wrapper for computing final score from Student_info object
    return grade(s.midterm, s.finals, s.homework);
}