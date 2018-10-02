#include <iostream>
#include <algorithm>
#include <string>
#include <iomanip> //setprecision
#include <vector>
//#include <stdexcept> //domain_error

#include "median.h"
#include "Student_info.h"
#include "grade.h"

using std::vector;
using std::setprecision;
//using std::domain_error;
using std::max;
using std::cout; using std::cin;
using std::endl;

int main() {

    vector<Student_info> students;
    Student_info record; //For holding each record
    //Parse stdin for records
    //Also get maxlen of name to format stuff properly
    std::string::size_type maxlen = 0;
    while (read(cin, record)) {
        students.push_back(record);
        maxlen = max(maxlen, record.name.size());
        //cout << record.name << grade(record) << endl;
    }
    
    double overall_grade;
    const int PADDING = 4; //Padding against max len for printing table
    auto prec = cout.precision();
    //Compute score and pretty print using setw() + left
    cout << std::setw(maxlen + PADDING) << std::left << "Name" << "Overall Grade" << endl;
    for (vector<Student_info>::size_type i = 0; i < students.size(); ++i) {
        try {
            overall_grade = grade(students[i]);
        } catch (std::domain_error e) {
            std::cerr << "Line " << i << ": " << e.what() << endl;
            continue;
        }
        cout << std::setw(maxlen + PADDING) << std::left << students[i].name 
            << setprecision(3) << overall_grade << prec << endl;
    }

    return 0;
}