#include <string>
#include <iostream>
#include <algorithm>
#include <cctype>
#include <cassert>

using std::getline;
using std::string;

// More verbose version
// bool check_palindrome(const string& s) {
//     //Left and right iterator
//     if (s.size() == 0) return false;
    
//     string::size_type i = 0, j = s.size() - 1;

//     while (i < j) {
//         if (std::tolower(s[i]) != std::tolower(s[j])) return false;
//         ++i; --j;
//     }

//     return true;
// }

// Concise version
// Equal compares to sequences to determine if they contain equal values
// First two are the sequence
// Second sequence is assumed same size (therefore no ending checking)
// s.rbegins() returns a reverse iterator going from back to end

char charlower(const char& c) {
    return std::tolower(c);
}

bool check_palindrome(string s) {
    // if (s.size() == 0) return false;
    // We need to create a quick wrapper for std::tolower to specify which version of the overloaded function we want
    std::transform(s.begin(), s.end(), s.begin(), charlower);
    return std::equal(s.begin(), s.end(), s.rbegin());
}

int main() {

    // Unit tests
    assert(!check_palindrome("ABAC"));
    assert(check_palindrome("Aba"));
    assert(check_palindrome("A"));
    assert(check_palindrome("Aa"));
    assert(check_palindrome(""));

    string s, longest_palin = "";
    size_t max_len = 0;
    while (std::cin >> s) {
        if (check_palindrome(s)) {
            if (max_len < s.size()) {
                max_len = s.size();
                longest_palin = s;
            }
        }
    }    

    if (max_len > 0)
        std::cout << "Longest palindrome: " << longest_palin << std::endl;

    return 0;
}