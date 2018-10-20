#include <string>
#include <algorithm>
#include <vector>
#include <iostream>
#include "xref.h"

using std::vector; using std::string;
using std::cin; using std::cout; using std::endl;

int main() {
    xref::cross_ref reference = xref::gen_cross_ref(cin);
    xref::print_xref(reference);

    return 0;
}