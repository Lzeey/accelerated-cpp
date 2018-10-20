//5-1 of C++ Accelerated
#include <iostream>
#include <iomanip>
#include <ios>
#include <string>
#include <vector>
#include <algorithm>

#include "split.h" //We use split as a helper here

using std::string; using std::vector;
using std::cin; using std::cout;
using std::getline;

struct Perm_index {
    string word;
    string phrase;
    string::size_type position;
};

vector<Perm_index> parse_index(std::istream& is) {
    vector<Perm_index> indices;
    string s;
    while (getline(is, s)) {
        vector<string> split_s = split(s);

        Perm_index idx;
        string::size_type position = 0; //Record starting position of word in string
        for (vector<string>::const_iterator it = split_s.begin(); it != split_s.end(); ++it) {
            idx.word = *it;
            idx.phrase = s;
            idx.position = position;
            // Shift position for next word. Assume single spacing.
            position += 1 + it->size();
            indices.push_back(idx);
        }
    }
    //Sort indices by the word order
    sort(indices.begin(), indices.end(), [](Perm_index a, Perm_index b) {return a.word < b.word;});

    return indices;
}

string::size_type width(const vector<Perm_index>& idxs) {
    string::size_type maxwidth = 0;
    for (vector<Perm_index>::const_iterator it = idxs.begin(); it != idxs.end(); ++it)
        maxwidth = std::max(maxwidth, it->phrase.size());
    return maxwidth;
}

void prettyprint(const vector<Perm_index>& idxs) {
    if (idxs.size() == 0) return;
    
    //Get width of thing. 2X allows for longest sentence to shift back and forth.
    //In order to avoid having too much whitespace dominating the output, we limit the maxwidth to 50 (phrases will be cut)
    auto maxlen = width(idxs);
    string::size_type MAXWIDTH = 30;
    auto maxwidth = std::min(maxlen, MAXWIDTH);

    cout << "Max width: " << maxwidth << std::endl;

    //for (vector<Perm_index>::const_iterator it = idxs.begin(); it != idxs.end(); ++it) {
    for (const auto& it : idxs) { //Super convenient iterator!
        //Ensure that the left_pad for the text does not underflow.
        auto left_pad = (maxwidth >= it.position) ? maxwidth - it.position : 0;
        //Contains left and right substring indices for the phrase (to truncate)
        auto start_pos = (maxwidth >= it.position) ? 0 : it.position - maxwidth;
        auto phrase_len = (it.phrase.size() < start_pos + 2 * maxwidth) ? it.phrase.size() - start_pos : 2 * maxwidth; 
        cout << std::setw(15) << std::left << it.word 
        << std::setw(5) << std::left << it.position
        << string(left_pad, ' ') + it.phrase.substr(start_pos, phrase_len) << std::endl;
    }
}

int main() {
    if (cin) {
        auto indices = parse_index(cin);
        prettyprint(indices);
    }
    return 0;
}