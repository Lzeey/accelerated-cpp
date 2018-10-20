#include <iostream>
#include <algorithm>
#include <string>
#include <iomanip> //setprecision
#include <vector>
#include <list>
//#include <stdexcept> //domain_error

#include "median.h"
#include "Student_info.h"
#include "grade.h"

using std::vector; using std::list;
using std::setprecision;
using std::string;
//using std::domain_error;
using std::max;
using std::cout; using std::cin;
using std::endl;

int main() {

    list<Student_info> students;
    Student_info record; //For holding each record
    //Parse stdin for records
    //Also get maxlen of name to format stuff properly
    std::string::size_type maxlen = 0;
    while (record.read(cin)) {
        students.push_back(record);
        maxlen = max(maxlen, record.name().size());
    }
    
    // Sort scores
    students.sort(compare);

    double overall_grade; string pass_msg;
    const int PADDING = 4; //Padding against max len for printing table
    auto prec = cout.precision();
    //Compute score and pretty print using setw() + left
    cout << std::setw(maxlen + PADDING) << std::left << "Name" << "Grade\tP/F" << endl;
    for (auto student : students) {
        try {
            overall_grade = student.grade();
            pass_msg = (failgrade(student))? "FAIL" : "PASS";
        } catch (std::domain_error e) {
            std::cerr << student.name() << ": " << e.what() << endl;
            continue;
        }
        cout << std::setw(maxlen + PADDING) << std::left << student.name() 
            << overall_grade
            //<< setprecision(4) << overall_grade << prec 
            << '\t' + pass_msg << endl;
    }

    return 0;
}