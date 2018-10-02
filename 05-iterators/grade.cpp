#include <vector>
#include <stdexcept>
#include <vector>
#include <list>

#include "median.h" //Median score
#include "Student_info.h"

using std::vector;
using std::list;

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

bool failgrade(const Student_info& s) {
    //Computes if the student failed the course
    // 60 is the imaginary passing grade
    return grade(s) < 60;
}

vector<Student_info> extract_fails(vector<Student_info>& students) {
    //Separate pass and fail grades for student records (inefficient)
    vector<Student_info> pass, fail;

    // Inefficient delete from vector
    vector<Student_info>::iterator iter = students.begin();
    while (iter != students.end()) {
        if (failgrade(*iter)) { //Deference iterator to return object
            fail.push_back(*iter);
            iter = students.erase(iter);
        } else {
            ++iter;
        }
    }
    return fail;
}

list<Student_info> extract_fails(list<Student_info>& students) {
    //Separate pass and fail grades for student records (more efficient)
    //C++ list is implemented as a double-linked list
    list<Student_info> pass, fail;

    // Inefficient delete from vector
    list<Student_info>::iterator iter = students.begin();
    while (iter != students.end()) {
        if (failgrade(*iter)) { //Deference iterator to return object
            fail.push_back(*iter);
            iter = students.erase(iter);
        } else {
            ++iter;
        }
    }
    return fail;
}