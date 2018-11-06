#ifndef GUARD_GRADE_H
#define GUARD_GRADE_H

#include <vector>
#include <list>
#include <string>
#include "Core.h"

double grade(const double&, const double&, const double&);
double grade(const double&, const double&, const std::vector<double>&);
double grade(const Core&);
bool failgrade(const Core&);
bool failgrade(const double&);
std::string letter_grade(const double&);    //Compute letter grade from raw overall grade
std::vector<Core> extract_fails(std::vector<Core>&);
std::list<Core> extract_fails(std::list<Core>&);
bool did_all_hw(const Core&);

#endif