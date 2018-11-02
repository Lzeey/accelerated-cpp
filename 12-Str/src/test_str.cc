/* Unit testing for List class */
#include <iostream>
#include <string>
#include <algorithm>

#include "Str.h"

using std::cout; using std::endl;

int test_init() {
    Str v; //Default constructor
    Str w("ASD"); //Explicit
    Str x("ASDB"); //Explicit
    Str y = w + x + "111";
    cout << y << '\n';
    cout << w << '\n';
    return 0;
}

int main() {
    test_init();
    cout << "All test passed\n";
    return 0;
}