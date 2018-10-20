#include <string>
#include <algorithm>
#include <vector>
#include <list>
#include <iostream>
#include "split.h"

using std::vector; using std::string;
using std::list;
using std::cin; using std::cout;

void test_split() {
    vector<string> strings;
    string s;
    while (std::getline(cin, s)) {
        auto tmp_strs = split(s);
        std::copy(tmp_strs.begin(), tmp_strs.end(), std::back_inserter(strings));
    }

    for (auto str : strings)
        cout << str << '\n';
}

void test_template_split() {
    vector<string> strings;
    string s;
    while (std::getline(cin, s)) {
        split(s, std::back_inserter(strings));
    }

    for (auto str : strings)
        cout << str << '\n';  
}

int main() {
    test_split();
    test_template_split();
    return 0;
}