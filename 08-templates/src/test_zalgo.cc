#include <vector>
#include <list>
#include <algorithm>
#include <cassert>
#include <iostream>

#include "zalgo.h"

using std::vector; using std::list;
using std::back_inserter;
using std::cout; using std::endl;

int test_equals() {
    vector<int> a = {0, 1, 2};
    list<int> b = {0, 1, 2};
    assert(zalgo::equal(a.begin(), a.end(), b.begin()));
    return 0;
}
int test_copy() {
    //Unit test for copy function
    vector<int> a = {0, 1, 2};
    list<int> b;
    zalgo::copy(a.begin(), a.end(), back_inserter(b));
    vector<int>::size_type idx = 0; //For indexing into a
    assert(zalgo::equal(a.begin(), a.end(), b.begin()));
    return 0;
}

int test_search() {
    vector<int> a = {0, 1, 2, 3};
    vector<int> b = {1,2};
    vector<int> c = {};
    vector<int> d = {3,4};
    assert(zalgo::search(a.begin(), a.end(), b.begin(), b.end()) != a.end());
    assert(zalgo::search(a.begin(), a.end(), c.begin(), c.end()) == a.begin());
    assert(zalgo::search(a.begin(), a.end(), d.begin(), d.end()) == a.end());
    return 0;
}

int test_find() {
    vector<int> a = {0, 1, 2};
    assert(zalgo::find(a.begin(), a.end(), 2) != a.end());
    assert(zalgo::find(a.begin(), a.end(), 3) == a.end());
    assert(zalgo::find(a.begin(), a.end(), 0) == a.begin());
    //Test using predicate
    assert(zalgo::find_if(a.begin(), a.end(), [](int x) {return ((x + 2) == 2);}) == a.begin());
    return 0;
}

int test_remove_copy() {
    vector<int> a = {0, 0, 1, 2};
    vector<int> b;
    vector<int> b_assert = {1, 2};
    zalgo::remove_copy(a.begin(), a.end(), back_inserter(b), 0);
    assert(zalgo::equal(b.begin(), b.end(), b_assert.begin()));
    vector<int> c;
    zalgo::remove_copy_if(a.begin(), a.end(), back_inserter(c), [](int x){return (x > -1);});
    assert(c.empty());
    return 0;
}

int test_remove() {
    vector<int> a = {0, 0, 1, 2};
    vector<int> a_assert = {1, 2};
    auto a_it = zalgo::remove(a.begin(), a.end(), 0);
    a.erase(a_it, a.end());
    assert(zalgo::equal(a.begin(), a.end(), a_assert.begin()));
    return 0;
}

int test_transform() {
    vector<int> a = {0, 0, 1, 2};
    vector<bool> b, b_assert = {true, true, false, false};
    zalgo::transform(a.begin(), a.end(), back_inserter(b), [](int x){return (x < 1);});
    assert(zalgo::equal(b.begin(), b.end(), b_assert.begin()));
    return 0;
}

int test_accumulate() {
    vector<double> a = {0.1, 0.2, 0.3, 0.4};
    assert(zalgo::accumulate(a.begin(), a.end(), 0.0) == 1.0);
    return 0;
}

int test_reverse() {
    vector<int> a = {1,2,3,4};
    vector<int> a_assert = {4,3,2,1};
    vector<int> b = {1};
    vector<int> b_assert = {1};
    vector<int> c;
    vector<int> c_assert;
    zalgo::reverse(a.begin(), a.end());
    assert(zalgo::equal(a.begin(), a.end(), a_assert.begin()));
    zalgo::reverse(b.begin(), b.end());
    assert(zalgo::equal(b.begin(), b.end(), b_assert.begin()));
    zalgo::reverse(c.begin(), c.end());
    assert(zalgo::equal(c.begin(), c.end(), c_assert.begin()));
    return 0;
}

int main() {
    test_equals();
    test_copy();
    test_search();
    test_find();
    test_remove_copy();
    test_remove();
    test_transform();
    test_accumulate();
    test_reverse();
    cout << "All test passed \n";
    return 0;
}