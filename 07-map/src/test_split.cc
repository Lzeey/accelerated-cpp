#include <string>
#include <algorithm>
#include <vector>
#include <iostream>
#include "split.h"

using std::vector; using std::string;
using std::cin; using std::cout;

int main() {
    vector<string> strings;
    string s;
    while (std::getline(cin, s)) {
        auto tmp_strs = split(s);
        std::copy(tmp_strs.begin(), tmp_strs.end(), std::back_inserter(strings));
    }

    for (auto str : strings)
        cout << str << '\n';

    return 0;
}