#ifndef GUARD_ANALYSIS_H
#define GUARD_ANALYSIS_H

#include <vector>
#include <string>

#include "Student_info.h"

namespace analysis {
    // Wrapper for throwing into transform function
    double median_grade(const Student_info& s);
    double average_grade(const Student_info& s);

    // Compute HW score just based on HW submitted
    double optimistic_median_grade(const Student_info& s);

    double analysis_wrapper(const std::vector<Student_info>& students,
                    double analysis_func(const std::vector<Student_info>&));

    void write_analysis(std::ostream& os, const std::string& name, 
                    double analysis_func(const Student_info&),
                    const std::vector<Student_info>& did,
                    const std::vector<Student_info>& didnt);

}
#endif