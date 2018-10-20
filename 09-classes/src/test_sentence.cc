#include <string>
#include <algorithm>
#include <vector>
#include <iostream>
#include "sentence.h"

using std::vector; using std::string;
using std::cin; using std::cout; using std::endl;

void print_grammar(const sentence::Grammar& g) {
    for (auto entry : g) {
        cout << entry.first << '\t';
        for (auto rule : entry.second) {
            for (auto word : rule)
                cout << word << sentence::is_word(word) << ' ';
            cout << '\n' << '\t';
        }
        cout << "-------\n";
    }
}

int main() {
    sentence::Grammar g = sentence::parse_grammar(cin);
    // for (auto pair : g) {
    //     cout << pair.first << endl;
    // }
    print_grammar(g);
    // sentence::gen_sentence(g);
    int NUM_SENTENCE = 100;
    for (int i=0; i != NUM_SENTENCE; ++i) {
        auto sen = sentence::gen_sentence_iterative(g);
        for (const string& word : sen)
            cout << word << ' ';
        cout << '\n';
    }

    return 0;
}