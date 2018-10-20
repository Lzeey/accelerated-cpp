#ifndef GUARD_XREF_H
#define GUARD_XREF_H
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include "split.h"

namespace xref {
    typedef std::map<std::string, std::vector<int> > cross_ref;
    void print_xref(const cross_ref&);
    cross_ref gen_cross_ref(std::istream&, std::vector<std::string> find_words(const std::string&) = split);
}
#endif