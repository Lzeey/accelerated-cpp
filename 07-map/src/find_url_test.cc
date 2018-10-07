#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cassert>

#include "find_url.h"

using std::cin; using std::getline;
using std::string; using std::vector;


int test_findurls() {
    size_t max_len = 0;
    string s;
    vector<string> urls;
    while (cin >> s) {
        vector<string> tmp_res = find_url::find_urls(s);
        // Copy results to back of res
        std::copy(tmp_res.begin(), tmp_res.end(), std::back_inserter(urls));
    }

    for (auto url: urls)
        std::cout << url << '\n';
    std::cout << urls.size() << "URLs found in test file" << std::endl;
    return 0;
}

int test_noturlchar() {
    assert(find_url::not_url_char(' '));
    assert(!find_url::not_url_char('a'));
    assert(find_url::not_url_char('^'));
    std::cerr << "not_url_char() passed" << '\n';
    return 0;
}

int main() {
    test_noturlchar();
    test_findurls();
    return 0;
}