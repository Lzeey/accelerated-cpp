#ifndef GUARD_SPLIT_H
#define GUARD_SPLIT_H

#include <vector>
#include <string>
#include <algorithm>

bool not_space(char);
bool is_space(char);
std::vector<std::string> split(const std::string&);
template <class Out>
void split(const std::string&, Out);

//#include "../src/split.cc"

/* Template version 
Takes a string and a output iterator*/
template <class Out>
void split(const std::string& s, Out os) { //N.B. should Out be specified with &?
    // Invariant - processed to i
    auto i = s.begin();
    while (i != s.end()) {
        //Ignore additional whitespaces
        i = std::find_if(i, s.end(), not_space);
        //Find end of word
        auto j = std::find_if(i, s.end(), is_space);
        // Ensure start of word is not at end
        if (i != s.end())
            *os++ = std::string(i, j); //Changed
        i = j;
    }
}

#endif