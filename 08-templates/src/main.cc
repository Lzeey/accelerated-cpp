#include <string>
#include <iostream>
#include <vector>
#include <cctype>

#include "split.h"

using std::string; using std::vector;
using std::cin; using std::cout; using std::endl;
using std::getline;

int main() {
    string s;
    while (getline(cin, s)) {
        cout << s << endl;
        vector<string> v = split(s);
        
        for (vector<string>::iterator iter = v.begin();
            iter != v.end(); ++iter) {
            cout << *iter << " ASD" << endl;
        }
    }

    return 0;
}