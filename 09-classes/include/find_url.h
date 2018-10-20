#ifndef GUARD_FIND_URL
#define GUARD_FIND_URL
#include <vector>
#include <string>

namespace find_url {
    std::string::const_iterator url_begin(std::string::const_iterator, std::string::const_iterator);
    std::string::const_iterator url_end(std::string::const_iterator, std::string::const_iterator);
    bool not_url_char(char c);
    /*
    Finds occurences of <protocol-name>://<resource-name> in a string
    <protocol-name> can only contain letters
    <resource-name> can have letters, digits, plus certain punctuations
    */
    std::vector<std::string> find_urls(const std::string&);
}

#endif