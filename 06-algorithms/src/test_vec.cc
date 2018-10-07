#include <vector>
#include <iostream>
#include <algorithm>

int main() {
    std::vector<int> u(10, 100);
    std::vector<int> v;
    std::copy(u.begin(), u.end(), v.end()); //Will result in seg fault!
    //std::copy(u.begin(), u.end(), std::back_inserter(v)); //Will result in seg fault!
    for (auto i : v) {
        std::cout << i << '\n';
    }
    return 0;
}