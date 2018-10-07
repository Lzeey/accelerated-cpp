#include <iostream>
#include <string>
#include <vector>

#include "Student_info.h"
#include "grade.h"
#include "analysis.h"

using std::vector;
using std::string;
using std::cout; using std::cin;
using std::endl;

int main() {

    // Quick analysis of grade differences between students who did all HW and those who did not
    // We employ two different grading schemes.
    // The first uses the median form of grading HW
    // The second uses an average (counting non-completed HW as 0)
    Student_info record; //For holding each record
    //Parse stdin for records
    vector<Student_info> did, didnt;
    while (read(cin, record)) {
        if (did_all_hw(record))
            did.push_back(record);
        else
            didnt.push_back(record);
    }

    if (did.empty()) {
        cout << "No students did all HW" << endl;
        return 1;
    } 
    else if (didnt.empty()) {
        cout << "All students did all HW" << endl;
    }

    // Run analysis
    analysis::write_analysis(cout, "Median", analysis::median_grade, did, didnt);
    analysis::write_analysis(cout, "Mean", analysis::average_grade, did, didnt);
    analysis::write_analysis(cout, "Optimistic", analysis::optimistic_median_grade, did, didnt);
    
    return 0;
}