#include <algorithm>
#include <random>
#include <string>
#include <map>
#include <vector>
#include <iostream>
#include <stdexcept>

#include "split.h"
#include "sentence.h"

using std::string; using std::vector;
using std::map;

/* Random sentence generator (Accelerated Cpp - 7.4)

We injest a grammar rule, such as the one below
Categories      Rules
---------------------------
<noun>          cat
<noun>          dog
<noun>          table
<noun-phrase>   <noun>
<noun-phrase>   <adjective> <noun-phrase>
<adjective>     large
<adjective>     brown
<adjective>     absurd
<verb>          jumps
<verb>          sits
<location>      on the stairs
<location>      under the sky
<location>      wherever it wants
<sentence>      the <noun-phrase> <verb> <location>

To randomly generate a sentence like
    the table jumps wherever it wants

We split the task into two parts. Parsing the grammar, and generating the sentence.

Each category is marked by <>, and may contain multiple rules (hence a RuleList).
The collection of categories is Grammar.
 */

namespace sentence {
    typedef vector<string> Rule;
    typedef vector<Rule> RuleList;
    typedef map<string, RuleList> Grammar;

    /* Parse grammar from input stream */
    Grammar parse_grammar(std::istream& is) {
        Grammar res;
        string line;
        while (std::getline(is, line)) {
            // Check of size of line
            vector<string> entry = split(line);
            if (entry.size() > 1) {
                //Use first entry as category. Rest as rule
                res[entry[0]].push_back(Rule(entry.begin() + 1, entry.end()));
            }
        }
        return res;
    }

    /* Generate sentence given grammar (recursive version) */
    vector<string> gen_sentence(const Grammar& g) {
        vector<string> res;
        gen_sentence_helper(g, "<sentence>", res);
        return res;
    }

    /* Predicate for checking if string is a word or category */
    bool is_word(const string& s) {
        return !(s.size() > 1 && s[0] == '<' && s[s.size() - 1] == '>');
    }

    /* Random uniform generator from [0, n) for indexing */
    size_t nrand(size_t n) {
        std::random_device rd; //For obtaining seed
        std::mt19937 gen(rd());
        std::uniform_int_distribution<size_t> dis(0, n-1);
        return dis(gen);
    }

    /* Recursive helper function to generate sentence */
    void gen_sentence_helper(const Grammar& g, const string& entry, vector<string>& res) {
        if (is_word(entry)) {
            res.emplace_back(entry);
        } else { //Is a category
            // Locate rule corresponding to category
            auto it = g.find(entry);
            if (it == g.end())
                throw std::logic_error("Rule not found: " + entry);

            // Get rule
            const RuleList& rlist = it->second;

            // Select one at random
            const Rule& selected_rule = rlist[nrand(rlist.size())];

            // Expand on ruleset
            for (auto item : selected_rule)
                gen_sentence_helper(g, item, res);
        }
    }

    /* Generate sentence given grammar (iterative version) - (7.6) */
    vector<string> gen_sentence_iterative(const Grammar& g) {
        // res stores the result to return. Top of the stack stores the next category to work on.
        vector<string> res, stack = {"<sentence>"};
        while (!stack.empty()) {
            // Extract and erase last element
            string entry = *(stack.end() - 1);
            stack.pop_back();

            // Parse into rules
            if (is_word(entry)) {
                res.emplace_back(entry);
            } else { //Is a category
                // Locate rule corresponding to category
                auto it = g.find(entry);
                if (it == g.end())
                    throw std::logic_error("Rule not found: " + entry);

                // Get rule
                const RuleList& rlist = it->second;

                // Select one at random
                const Rule& selected_rule = rlist[nrand(rlist.size())];

                // Place the entries onto the stack - in reverse order
                std::reverse_copy(selected_rule.begin(), selected_rule.end(), std::back_inserter(stack));
            }
        }

        return res;
    }
}