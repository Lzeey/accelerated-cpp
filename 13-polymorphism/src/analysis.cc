#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <vector>
#include <string>
#include <numeric>

#include "Student_info.h"
#include "grade.h"
#include "median.h"
#include "average.h"
#include "analysis.h"

namespace analysis {
    using std::string; using std::vector;
    using std::transform; using std::accumulate;
    using std::domain_error;

    // Wrapper for throwing into transform function
    double median_grade(const Student_info& s) {
        try {
            return grade(s);
        } catch (domain_error) {
            return grade(s.midterm, s.finals, 0);
        }
    }

    double average_grade(const Student_info& s) {
        return grade(s.midterm, s.finals, average(s.homework));
    }

    // Compute HW score just based on HW submitted
    double optimistic_median_grade(const Student_info& s) {
        vector<double> nonzero;
        std::remove_copy(s.homework.begin(), s.homework.end(), std::back_inserter(nonzero), 0);

        if (nonzero.empty())
            return grade(s.midterm, s.finals, 0);
        else
            return grade(s.midterm, s.finals, median(nonzero));
    }

    double analysis_wrapper(const vector<Student_info>& students,
                    double analysis_func(const Student_info&)) 
    {
        vector<double> grades;
        transform(students.begin(), students.end(), std::back_inserter(grades), analysis_func);
        return median(grades);
    }

    void write_analysis(std::ostream& os, const string& name, 
                    double analysis_func(const Student_info&),
                    const vector<Student_info>& did,
                    const vector<Student_info>& didnt) 
    {

        os << "Analysis: " << name << '\n'
            << "==============\n"
            << "median(did) = " << analysis_wrapper(did, analysis_func) << '\n'
            << "median(didnt) = " << analysis_wrapper(didnt, analysis_func) 
            << "\n\n";

    }
}