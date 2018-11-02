/* Unit testing for List class */
#include <iostream>
#include <string>
#include <algorithm>

#include "List.h"

using std::cout; using std::endl;

int test_init() {
    List<int> v; //Default constructor
    List<double> w(10); //Explicit
    List<std::string> strings(1, "Hello"); //Explicit
    strings.push_back("BBB");

    List<std::string> y = strings; //Assignment test
    // assert(y == strings); //TOFIX
    std::copy(strings.begin(), strings.end(), std::back_inserter(y));
    assert(y.size() == strings.size() * 2);

    strings.erase(strings.begin());
    assert(strings.size() == 1);
    assert(*(strings.begin()) == "BBB");
    //Initialization with rvalue
    List<int> a = List<int>(3, 2);

    return 0;
}

int test_methods() {
    List<int> a = List<int>();
    assert(a.size() == 0);
    assert(a.empty());

    List<int> b(2,3);
    assert(!b.empty());
    assert(b.size() == 2);

    b.push_back(1);
    assert(*(--b.end()) == 1);
    return 0;
}

int main() {
    test_init();
    test_methods();

    cout << "All test passed\n";
    return 0;
}