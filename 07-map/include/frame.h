#ifndef GUARD_FRAME_H
#define GUARD_FRAME_H

#include <string>
#include <vector>

//Frame function. To wrap a string with a frame
std::vector<std::string> frame(const std::vector<std::string>&, int pad = 2);

// Centers the vector of strings by padding left and right appropriately
// If use_frame is true, uses frame() on the result as well
std::vector<std::string> center(const std::vector<std::string>&, bool use_frame=false);

//Extracts maximum string width from vector of string
//Returns 0 if empty vector
std::string::size_type width(const std::vector<std::string>&);

//Horizontal concatenation by top margin
std::vector<std::string> hcat(const std::vector<std::string>&, const std::vector<std::string>&);
//Vertical concatenation by left margin
std::vector<std::string> vcat(const std::vector<std::string>&, const std::vector<std::string>&);
//Helper for printing vector<string> on cout
void print_vec_str(const std::vector<std::string>&);
#endif