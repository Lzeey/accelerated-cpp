#include <algorithm>
#include <string>
#include <iostream>

using std::string;

int main() {
    string s = "ABCDEFG";
    string search_term = "BCD";
    auto it = std::search(s.begin(), s.end(), search_term.begin(), search_term.end());
    if (it != s.end()) {
        std::cout << "Found at offset " << it - s.begin() << '\n';
    }

    return 0;
}