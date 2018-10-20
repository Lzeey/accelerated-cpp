#ifndef GUARD_GRADE_H
#define GUARD_GRADE_H

#include <vector>
#include <list>
#include <string>
#include "Student_info.h"

double grade(const double&, const double&, const double&);
double grade(const double&, const double&, const std::vector<double>&);
double grade(const Student_info&);
bool failgrade(const Student_info&);
bool failgrade(const double&);
std::string letter_grade(const double&);    //Compute letter grade from raw overall grade
std::vector<Student_info> extract_fails(std::vector<Student_info>&);
std::list<Student_info> extract_fails(std::list<Student_info>&);
bool did_all_hw(const Student_info&);

#endif