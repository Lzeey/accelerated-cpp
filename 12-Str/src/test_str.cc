/* Unit testing for List class */
#include <iostream>
#include <string>
#include <cstring>
#include <algorithm>
#include <cassert>

#include "Str.h"

using std::cout; using std::endl;
using std::cin;

int test_init() {
    Str v; //Default constructor
    assert(v.empty());
    assert(v.empty());
    Str w("ASD"); //Explicit
    assert(!w.empty());
    assert(w.size() == 3);
    
    Str x = "testing"; //Initialization
    assert(x.size() == 7);
    Str y = w + x + "111";
    assert(y.size() == (w.size() + x.size() + 3));
    std::string zz = "testing";
    Str z(zz.begin(), zz.end());
    assert(z.size() == zz.size());
    //Test for equality matching
    assert(z == "testing");
    assert(z != "testin");
    assert(x == z);

    //Test for copy
    Str a = "hello";
    char aa[7];
    a.copy(aa, sizeof aa);
    aa[a.size()] = '\0';
    assert(strlen(aa) == a.size());
    assert(strcmp(aa, "hello") == 0);

    //Conversion
    assert(a); //boolean operator

    //std::string test
    std::string b = "olé";
    // cout << b.size() << '\n'; //4! Holy shit no UTF-8 support
    Str bb = b.c_str();
    cout << bb << endl;
    // cout << bb.size() << '\n';

    //Test stdin
    Str c;
    cin >> c; // hello
    assert(c == "helloo");
    cin >> c;
    assert(c == "world");
    assert(c < "www");
    assert(c > "aaa");
    //Test getline
    Str d;
    getline(cin, d);
    cout << d << endl;
    
    return 0;
}

int main() {
    test_init();
    cout << "All test passed\n";
    return 0;
}