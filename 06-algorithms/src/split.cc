#include <vector>
#include <string>
#include <cctype>

#include "split.h"

using std::vector; using std::string;

vector<string> split(const string& s) {
    vector<string> res;
    typedef string::size_type str_size;
    //invariant: processed to i)
    str_size i = 0;
    while (i < s.size()) {
        //Skip all whitespaces
        //invariant: [original i, i) are whitespaces
        while (i < s.size() && std::isspace(s[i]))
            ++i;

        //Find end of next word
        //invariant: [i, j) are non-whitespace
        str_size j = i;
        while (j < s.size() && !std::isspace(s[j]))
            ++j;
        
        if (i != j) {
            res.push_back(s.substr(i, j-i));
            i = j;
        }
    }
    return res;
}