#include <string>
#include <algorithm>
#include <vector>
#include <iostream>

using std::vector; using std::string;
using std::cin; using std::cout;

string concat_strs(const vector<string>& v) {
    string res = "";
    for (const string& s : v) {
        std::copy(s.begin(), s.end(), std::back_inserter(res));
    }
    return res;
}

int main() {
    vector<string> strings;
    string s;
    while (std::getline(cin, s)) {
        strings.emplace_back(s);
    }

    cout << concat_strs(strings) << '\n';
    return 0;
}