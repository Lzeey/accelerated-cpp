#include <vector>
#include <string>
#include <cctype>
#include <algorithm>

#include "split.h"

using std::vector; using std::string;

/* Verbose version */
// vector<string> split(const string& s) {
//     vector<string> res;
//     typedef string::size_type str_size;
//     //invariant: processed to i)
//     str_size i = 0;
//     while (i < s.size()) {
//         //Skip all whitespaces
//         //invariant: [original i, i) are whitespaces
//         while (i < s.size() && std::isspace(s[i]))
//             ++i;

//         //Find end of next word
//         //invariant: [i, j) are non-whitespace
//         str_size j = i;
//         while (j < s.size() && !std::isspace(s[j]))
//             ++j;
        
//         if (i != j) {
//             res.push_back(s.substr(i, j-i));
//             i = j;
//         }
//     }
//     return res;
// }

/* Predicates for split function */
bool not_space(char c) {
    return !isspace(c);
}

bool is_space(char c) {
    return isspace(c);
}

/* Concise version */
vector<string> split(const string& s) {
    vector<string> res;
    //Invariant - processed to i)
    auto i = s.begin();
    while (i != s.end()) {
        //Ignore additional whitespaces
        i = std::find_if(i, s.end(), not_space);
        // Find end of word
        auto j = std::find_if(i, s.end(), is_space);
        // Ensure start of word is not at end
        if (i != s.end())
            res.emplace_back(string(i, j));
        i = j;
    }
    return res;
}
