/* Unit testing for Vec class */
#include <iostream>
#include <string>
#include <cassert> //assert

#include "Vec.h"

using std::cout; using std::endl;

int test_init() {
    Vec<int> v; //Default constructor
    Vec<double> w(10); //Explicit
    Vec<std::string> strings(2, "Hello"); //Explicit
    strings.push_back("BBB");
    //cout << strings;
    // for (auto i: strings)
    //     cout << i << '\n';
    // for (Vec<std::string>::const_iterator it = strings.begin(); it != strings.end(); ++it) {
    //     cout << *it << '\n';
    // }

    Vec<std::string> y = strings; //Assignment test
    // for (auto i: y) {
    //     cout << i << '\n';
    // }

    //Initialization with rvalue
    Vec<int> a = Vec<int>(3, 2);

    strings.pop_back();
    assert(strings.size() == 2);
    Vec<int> s(1, 2);
    s.pop_back();
    assert(s.empty());
    s.push_back(1);
    assert(s.size() == 1);

    //Initialization with iterators
    Vec<int> b(a.begin(), a.end());
    assert(b.size() == a.size());

    return 0;
}

int test_methods() {
    Vec<int> a;
    assert(a.empty());

    Vec<int> b(2,3);
    assert(!b.empty());
    b.clear();
    assert(b.empty());

    //Erase test (single)
    Vec<int> c = {2,3};
    c.erase(c.begin()); 
    assert(c.size() == 1);
    assert(*(c.begin()) == 3);
    Vec<int>::iterator c_it = c.erase(c.begin());
    assert(c_it == c.end());
    assert(c.empty());

    //Erase test (range)
    Vec<int> d = {1,2,3,4};
    cout << d << endl;
    d.erase(d.begin() + 1, d.begin() + 3);
    assert(d.size() == 2);
    d.erase(d.begin(), d.end());
    assert(d.empty());

    return 0;
}

int main() {
    test_init();
    test_methods();
    cout << "All test passed (Vector)\n";
    return 0;
}