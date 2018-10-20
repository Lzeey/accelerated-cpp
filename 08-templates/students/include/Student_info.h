#ifndef GUARD_Student_info
#define GUARD_Student_info

#include <vector>
#include <string>
#include <iostream>

struct Student_info {
    std::string name;
    double midterm, finals;
    std::vector<double> homework;
};

bool compare(Student_info&, Student_info&);
std::istream& read(std::istream&, Student_info&);
std::istream& read_hw(std::istream&, std::vector<double>&);

#endif