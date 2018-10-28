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
    //cout << strings;
    for (auto i: strings)
        cout << i << '\n';
    // for (Vec<std::string>::const_iterator it = strings.begin(); it != strings.end(); ++it) {
    //     cout << *it << '\n';
    // }

    Vec<std::string> y = strings; //Assignment test
    for (auto i: y) {
        cout << i << '\n';
    }

    //Initialization with rvalue
    Vec<int> a = Vec<int>(3, 2);
    // for (const auto& i: a) {
    //     cout << i << '\n';
    // }
    cout << a;

    return 0;
}

int test_methods() {
    Vec<int> a;
    assert(a.empty());

    Vec<int> b(2,3);
    assert(!b.empty());

    return 0;
}

int main() {
    test_init();
    test_methods();

    return 0;
}