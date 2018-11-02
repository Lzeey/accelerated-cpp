#ifndef GUARD_STRING_H
#define GUARD_STRING_H

// Implementation of String using direct memory allocation

#include <algorithm>
#include <iterator> //back_inserter
#include <iostream>

#include "Vec.h"
/* Acclereated Cpp - Chapter 12. String class.
Modified to be consistent with C++11 

Str will store a null-terminated string.*/
class Str {
    public:
        typedef Vec<char>::size_type size_type;
        typedef Vec<char>::iterator iterator;
        typedef Vec<char>::const_iterator const_iterator;

        // Constructors
        Str(): data(1, '\0') {}    //Default constructor
        Str(const char* c) {std::copy(c, c + sizeof(c), std::back_inserter(data));} //Copy null terminated char as well
        Str(size_type n, char c): data(n, c) {data.push_back('\0');};
        template<class FwdIter> Str(FwdIter b, FwdIter e) {
            std::copy(b, e, std::back_inserter(data));
            data.push_back('\0');
        }

        //Interfaces
        char& operator[] (size_type i) {return data[i];}
        const char& operator[] (size_type i) const {return data[i];}
        Str& operator+=(const Str& s) {
            append(s);
            return *this;
        }
        Str operator+(const Str& s) const {
            Str res = *this;
            res.append(s);
            return res;
        }
        friend std::ostream& operator<<(std::ostream&, const Str&);
        friend std::istream& operator>>(std::istream&, Str&);

        //Iterators
        iterator begin() {return data.begin();}
        const_iterator begin() const {return data.begin();}
        iterator end() {return data.end() - 1;}
        const_iterator end() const {return data.end() - 1;}
        //Methods
        size_type size() const {return data.size() - 1;}
        const char* c_str() const {return data.begin();} //Return a pointer to the actual string. Implementation since C++11.
        Str& append(size_type n, char c);
        Str& append( const Str& str );
        Str& append( const char* s );
    private:
        Vec<char> data;
};

std::ostream& operator<<(std::ostream& os, const Str& s) {
    for (Str::size_type i = 0; i != s.size(); ++i)
        os << s[i];
    return os;
}

std::istream& operator>>(std::istream& is, Str& s) {
    char c; //char to input
    while (is >> c) {
        s.data.push_back(c);
    }
    s.data.push_back('\0');
    return is;
}

// Append methods. Main way of adding stuff to Str
// Invariant: assumes that Str is already properly initialized (data has \0 at the end)
Str& Str::append(size_type n, char c) {
    data.pop_back(); //Remove \0
    for (size_type i = 0; i != n; i++) {
        data.push_back(c);
    }
    data.push_back('\0');
    return *this;
}

Str& Str::append( const Str& str ) {
    data.pop_back();
    std::copy(str.begin(), str.end(), std::back_inserter(data));
    data.push_back('\0');
    return *this;
}
Str& Str::append( const char* c ) {
    data.pop_back();
    std::copy(c, c + sizeof(c), std::back_inserter(data));
    return *this;
}
#endif