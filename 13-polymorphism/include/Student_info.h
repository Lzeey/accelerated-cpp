#ifndef GUARD_Student_info
#define GUARD_Student_info

#include <vector>
#include <string>
#include <iostream>

#include "Core.h"

// Handle class for base type Core.
// Includes Grad and Core for now

class Student_info {
    public:
        // Constructors
        Student_info() = default;     // Default constructor
        Student_info(std::istream& is) {read(is);} // Construct by reading stream

        Student_info(const Student_info&); //Copy constructor
        Student_info& operator=(Student_info); //Assignment
        ~Student_info() {delete cp;} //Destructor - through virtual function
        friend void swap(Student_info&, Student_info&);
        // Accessor functions
        std::string type() const {return student_type;}
        std::istream& read(std::istream&);

        // Wrapper for virtual functions
        std::string name() const {
            if (cp)
                return cp->name();
            else
                throw std::runtime_error("Uninitialized student");
        }
        double grade() const {
            if (cp) {
                return cp->grade();
            } else {
                throw std::runtime_error("Uninitialized student");
            }
        }
        // Business logic here
        double failed() const {
            if (cp) {
                return cp->failed();
            } else {
                throw std::runtime_error("Uninitialized student");
            }
        }

        static bool compare(const Student_info& s1, const Student_info& s2) {
            return s1.name() < s2.name();
        }

    private:
        Core *cp = nullptr;
        std::string student_type;
};

// bool compare_ptr(const Core* cp1, const Core* cp2) {
//     return compare(*cp1, *cp2);
// }

#endif