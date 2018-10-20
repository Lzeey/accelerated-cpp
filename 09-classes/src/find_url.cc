#include <vector>
#include <string>
#include <algorithm>
#include <cctype>
#include "find_url.h"

namespace find_url {
    using std::string; using std::vector;

    string::const_iterator url_begin(string::const_iterator begin, string::const_iterator end) {
        // TODO: TO BE IMPLEMENTED
        // First hunt for prescence of ://
        static const string sep = "://";
        typedef string::const_iterator iter;

        // i marks start of separator
        iter i = begin;
        // The assignment yields i, which is then immediatedly used for comparison
        while ((i = search(begin, end, sep.begin(), sep.end())) != end) {

            //Ensure separate is not at start or end of line -> We have found something promising
            if (i != begin && i + sep.size() != end) {
                // beg is for start of protocol name
                iter beg = i;
                while (beg != begin && std::isalpha(beg[-1])) //beg[-1] is short for *(beg - 1)
                    --beg;
                
                // At least one character found before and after separator?
                if (beg != i && !not_url_char(i[sep.size()]))
                    return beg;
            }
            // Not a valid URL. We advance past the separator.
            i += sep.size();
        }
        return end;
    }

    string::const_iterator url_end(string::const_iterator begin, string::const_iterator end) {
        return find_if(begin, end, not_url_char);
    }

    bool not_url_char(char c) {
        // Bunch of valid chars in URLs
        static const string url_chars = "~;/?:@=&$-_.+!*'(),";

        return !(std::isalnum(c) || std::find(url_chars.begin(), url_chars.end(), c) != url_chars.end());
    }

    /*
    Finds occurences of <protocol-name>://<resource-name> in a string
    <protocol-name> can only contain letters
    <resource-name> can have letters, digits, plus certain punctuations
    */
    vector<string> find_urls(const string& s) {
        vector<string> res;
        typedef string::const_iterator iter;
        iter b = s.begin(), e = s.end();

        while (b != e) {
            // Get beginning of URL
            b = url_begin(b, e);

            if (b != e) { //If found
                // Get end of URL
                iter ending = url_end(b, e);
                res.emplace_back(string(b, ending));

                // Advance b and get more URLs
                b = ending;
            }
        }
        return res;
    }

}
