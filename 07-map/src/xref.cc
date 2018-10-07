#include <iostream>
#include <vector>
#include <string>
#include <map>
#include "split.h"
#include "xref.h"

/* To generate cross-reference from a chunk of text */
using std::vector; using std::string;
using std::map; using std::cout; using std::endl;

namespace xref {
    typedef map<string, vector<int> > cross_ref;
    void print_xref(const cross_ref& x) {
        if (x.size() == 0) return;

        /*Pretty prints xref*/
        cout << "Word\tPages\n" << string(10, '-') << '\n'; 
        for (auto pair : x) {
            cout << pair.first << ": \t";
            for (auto page : pair.second)
                cout << page << ' ';
            cout << endl;
        }
    }

    cross_ref gen_cross_ref(std::istream& is, vector<string> find_words(const string&)) {
        /*Extracts a cross-reference data structure from input stream*/
        map<string, vector<int> > res;

        // Parse input stream
        string line; int line_num = 0;
        while (std::getline(is, line)) {
            ++line_num;
            // Extract words from line
            auto words = find_words(line);
            // Store into results
            for (auto word : words) {
                // Check if line number is already inside
                if (res[word].size() == 0 || res[word][res[word].size() - 1] != line_num)
                    res[word].push_back(line_num);
            }
        }
        return res;
    }
}