#ifndef GUARD_Student_info
#define GUARD_Student_info

#include <vector>
#include <string>
#include <iostream>

struct Student_info {
    public:
        // Constructors
        Student_info();     // Default constructor
        Student_info(std::istream&); // Construct by reading stream
        // Accessor functions
        std::string name() const {return n;};
        double grade() const {return grd;};
        // Validity check. Run before running grade.
        bool valid() const {return !homework.empty();};
        std::istream& read(std::istream&);
        // Business logic here
        double failed() const;

    private:
        std::string n;
        double midterm, finals;
        double grd; // Grade
        std::vector<double> homework;
        std::istream& read_hw(std::istream&, std::vector<double>&);
};

bool compare(Student_info&, Student_info&);

#endif