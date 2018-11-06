#ifndef GUARD_GRAD_H
#define GUARD_GRAD_H

// Grad object, inheriting Core for all Grad students attending course
// Has extra requirements of Thesis component.
// grade is min of traditional grade vs thesis grade.

#include <vector>
#include <string>
#include <iostream>

#include <Core.h>

class Grad: public Core {
    public:
        // Constructors
        Grad() = default;     // Default constructor
        Grad(std::istream&); // Construct by reading stream
        virtual double grade() const; //Special grading function for grad students
        virtual std::istream& read(std::istream&);

    private:
        double thesis = 0;
};

#endif