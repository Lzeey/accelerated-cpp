#ifndef GUARD_SENTENCE_H
#define GUARD_SENTENCE_H
#include <algorithm>
#include <random>
#include <string>
#include <map>
#include <vector>
#include <iostream>

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
    typedef std::vector<std::string> Rule;
    typedef std::vector<Rule> RuleList;
    typedef std::map<std::string, RuleList> Grammar;

    /* Parse grammar from input stream */
    Grammar parse_grammar(std::istream&);

    /* Generate sentence given grammar */
    std::vector<std::string> gen_sentence(const Grammar&);

    /* Predicate for checking if std::string is a word or category */
    bool is_word(const std::string&);

    /* Random uniform generator from [0, n) for indexing */
    size_t nrand(size_t n);

    /* Recursive helper function to generate sentence */
    void gen_sentence_helper(const Grammar&, const std::string&, std::vector<std::string>&);

    /* Generate sentence given grammar (iterative version) */
    std::vector<std::string> gen_sentence_iterative(const Grammar&);
}

#endif