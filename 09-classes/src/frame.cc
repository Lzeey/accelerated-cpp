#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

#include "frame.h"

using std::string; using std::vector;
typedef string::size_type str_size;


//Frame function. To wrap a string around with '*'s
vector<string> frame(const vector<string>& v, int pad) {

    str_size maxwidth = width(v);
    vector<string> res;

    // Create the border. The width is determined by max width + padding and one '*' frame character (on both sides)
    string border(maxwidth + pad*2 + 2, '*');
    res.push_back(border);

    for (vector<string>::size_type i = 0; i!=v.size(); ++i)
        res.push_back('*' + string(pad, ' ') + v[i] 
            + string(pad + maxwidth - v[i].size(), ' ') + '*');

    //Closing border
    res.push_back(border);

    return res;
}

//Vertical concatenation by left margin
vector<string> vcat(const vector<string>& top, const vector<string>& btm) {
    //Copy the top picture (as a base)
    vector<string> res = top;

    //Copy bottom picture
    for (vector<string>::const_iterator s = btm.begin(); s != btm.end(); ++s)
        res.push_back(*s);

    return res;
}

//Horizontal concatenation by left margin
vector<string> hcat(const vector<string>& left, const vector<string>& right) {

    vector<string> res;

    //Ensure that all right outputs starts AFTER the maximum left input vertical margin
    string::size_type left_width = width(left);

    //Indices for left and right respectively
    vector<string>::size_type i = 0, j = 0; 
    
    while (i != left.size() || j != right.size()) {
        string s = "";

        //Check for left input
        if (i != left.size())
            s += left[i++];
        //Pad
        s += string(left_width - s.size(), ' ');

        //Copy right
        if (j != right.size())
            s += right[j++];
        
        res.push_back(s);
    }

    return res;
}

// Centers the vector of strings by padding left and right appropriately
// If use_frame is true, uses frame() on the result as well
vector<string> center(const vector<string>& lines, bool use_frame) {
    vector<string> res;
    auto maxlen = width(lines);

    for (const auto& line: lines) {
        //We subdivide each
        auto left_pad = (maxlen - line.size()) / 2;
        auto right_pad = maxlen - line.size() - left_pad;
        res.push_back(string(left_pad, ' ') + line + string(right_pad, ' '));
    }
    if (use_frame)
        res = frame(res);
    return res;
}


str_size width(const vector<string>& v) {
    str_size maxlen = 0;
    for (vector<string>::const_iterator s = v.begin(); s != v.end(); ++s)
        maxlen = std::max(maxlen, s->size());
    return maxlen;
}

void print_vec_str(const vector<string>& v) {
    for (std::vector<std::string>::size_type i = 0; i != v.size(); ++i) {
        std::cout << v[i] << std::endl;
    }
}