#ifndef GUARD_CORE_H
#define GUARD_CORE_H

// Core object for all students attending course

#include <vector>
#include <string>
#include <iostream>

class Core {
    public:
        friend class Student_info; //Handler class

        // Constructors
        Core() = default;     // Default constructor
        Core(std::istream&); // Construct by reading stream

        // Destructor
        virtual ~Core() {} // So that handle class Student_info can destroy pointer
        // Accessor functions
        std::string name() const {return name_;}
        virtual double grade() const;

        //Methods
        // Validity check. Run before running grade.
        bool valid() const {return !homework.empty();}
        virtual std::istream& read(std::istream&);
        // Business logic here
        double failed() const;

    protected:
        virtual Core* clone() const {return new Core(*this);} //Copy constructor for handler class
        double midterm = 0, finals = 0;
        double grd = 0; // Grade (????) TODO: REMOVE?
        std::vector<double> homework;
        std::istream& read_common(std::istream&);
        std::istream& read_hw(std::istream&, std::vector<double>&);

    private:
        std::string name_;
};

bool compare(const Core&, const Core&);

#endif