/* Unit testing for Vec class */
#include <iostream>
#include <string>

#include "Vec.h"

using std::cout; using std::endl;

int test_init() {
    Vec<int> v; //Default constructor
    Vec<double> w(10); //Explicit
    Vec<std::string> strings(2, "Hello"); //Explicit
    strings.push_back("BBB");
    for (Vec<std::string>::const_iterator it = strings.begin(); it != strings.end(); ++it) {
        cout << *it << '\n';
    }

    Vec<std::string> y = strings; //Assignment test
    for (Vec<std::string>::const_iterator it = y.begin(); it != y.end(); ++it) {
        cout << *it << '\n';
    }
    return 0;
}

int main() {
    test_init();
    return 0;
}