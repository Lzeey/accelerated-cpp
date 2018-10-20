#include <algorithm>
#include <stdexcept>
#include <vector>
#include <list>
#include <string>

#include "median.h" //Median score
#include "Student_info.h"

using std::vector;
using std::list;
using std::string;

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

// double grade(const Student_info& s) {
//     //Wrapper for computing final score from Student_info object
//     return grade(s.midterm, s.finals, s.homework);
// }

bool failgrade(const double& grade) {
    //Computes if the student failed the course
    // 60 is the imaginary passing grade
    return grade < 60;
}

bool failgrade(const Student_info& s) {
    //Computes if the student failed the course
    // 60 is the imaginary passing grade
    return failgrade(s.grade());
}

std::string letter_grade(const double& grade) {    
    //Compute letter grade from raw overall grade
    static const double grades[] = {97, 94, 90, 87, 84, 80, 77, 74, 70, 60, 0};
    static const std::string letters[] = {"A+", "A", "A-", "B+", "B", "B-", "C+", "C", "C-", "D", "F"};
    // Compute number of grades using size of array and size of single element
    // WARNING: THIS IS ONLY FOR EXERCISES PURPOSES. USE STL CONTAINERS (e.g. vector)
    // EXAMPLE: http://www.cplusplus.com/forum/beginner/3699/ -> See failure
    static const size_t ngrades = sizeof(grades)/sizeof(*grades);
    for (size_t i = 0; i != ngrades; ++i) {
        if (grade >= grades[i])
            return letters[i]; 
    }
    // Use escape to avoid internationalisation problems
    // C++ strings should not have two consecutive ??
    return "?\?\?";
}

// vector<Student_info> extract_fails(vector<Student_info>& students) {
//     //Separate pass and fail grades for student records (inefficient)
//     vector<Student_info> pass, fail;

//     // Inefficient delete from vector
//     vector<Student_info>::iterator iter = students.begin();
//     while (iter != students.end()) {
//         if (failgrade(*iter)) { //Deference iterator to return object
//             fail.push_back(*iter);
//             iter = students.erase(iter);
//         } else {
//             ++iter;
//         }
//     }
//     return fail;
// }

// list<Student_info> extract_fails(list<Student_info>& students) {
//     //Separate pass and fail grades for student records (more efficient)
//     //C++ list is implemented as a double-linked list
//     list<Student_info> pass, fail;

//     // Inefficient delete from vector
//     list<Student_info>::iterator iter = students.begin();
//     while (iter != students.end()) {
//         if (failgrade(*iter)) { //Deference iterator to return object
//             fail.push_back(*iter);
//             iter = students.erase(iter);
//         } else {
//             ++iter;
//         }
//     }
//     return fail;
// }

//6.2.1 Check if student did all HW
// bool did_all_hw(const Student_info& s) {
//     return (std::find(s.homework.begin(), s.homework.end(), 0) == s.homework.end());
// }

// vector<Student_info> separate_completed_hw(const vector<Student_info>& students,
//                                             vector<Student_info>& did, //Those who completed their HW
//                                             vector<Student_info>& didnt) { //Those who didn't
    

// }