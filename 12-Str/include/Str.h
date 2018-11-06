#ifndef GUARD_STRING_H
#define GUARD_STRING_H

// Implementation of String using direct memory allocation

#include <algorithm>
#include <iterator> //back_inserter
#include <iostream>
#include <cstring> // strcmp
#include <stdexcept> //istream, ostream
#include <iterator> // ostream_iterator

#include "Vec.h"
/* Acclereated Cpp - Chapter 12. String class.
Modified to be consistent with C++11 

Str will store a null-terminated string.*/
class Str {
    public:
        typedef Vec<char>::size_type size_type;
        typedef Vec<char>::iterator iterator;
        typedef Vec<char>::const_iterator const_iterator;
        typedef char value_type;

        // Constructors
        Str(): chars(1, '\0') {}    //Default constructor
        Str(const char* c) { //Copy null terminated char as well
            std::copy(c, c + strlen(c), std::back_inserter(chars));
            chars.push_back('\0');} 
        Str(size_type n, char c): chars(n, c) {chars.push_back('\0');}
        template<class FwdIter> Str(FwdIter b, FwdIter e) {
            std::copy(b, e, std::back_inserter(chars));
            chars.push_back('\0');
        }

        //Interfaces
        char& operator[] (size_type i) {return chars[i];}
        const char& operator[] (size_type i) const {return chars[i];}
        Str& operator+=(const Str& s) {
            append(s);
            return *this;
        }
        Str operator+(const Str& s) const {
            Str res = *this; //Use copy constructor for new object
            res.append(s);
            return res;
        }
        Str operator+(const char* c) const {
            Str res = *this; //Use copy constructor for new object
            res.append(c);
            return res;
        }
        bool operator==(const Str& s) const { //Equality
            return std::equal(s.begin(), s.end(), this->begin(), this->end());
        }
        bool operator==(const char* c) const { //Not required due to conversion, but written for efficiency
            return std::equal(c, c+strlen(c), this->begin(), this->end());
        }
        bool operator!=(const Str& s) const {
            return !std::equal(s.begin(), s.end(), this->begin(), this->end());
        }
        bool operator!=(const char* c) const { //Not required due to conversion, but written for efficiency
            return !std::equal(c, c+strlen(c), this->begin(), this->end());
        }
        bool operator<(const Str& s) const {
            return (strcmp(this->c_str(), s.c_str()) < 0);
        }
        bool operator>(const Str& s) const {
            return (strcmp(this->c_str(), s.c_str()) > 0);
        }
        bool operator<=(const Str& s) const {
            return (strcmp(this->c_str(), s.c_str()) <= 0);
        }
        bool operator>=(const Str& s) const {
            return (strcmp(this->c_str(), s.c_str()) >= 0);
        }

        friend std::ostream& operator<<(std::ostream&, const Str&);
        friend std::istream& operator>>(std::istream&, Str&);
        friend std::istream& getline(std::istream&, Str&);

        //Iterators
        iterator begin() {return chars.begin();}
        const_iterator begin() const {return chars.begin();}
        iterator end() {return chars.end() - 1;}
        const_iterator end() const {return chars.end() - 1;}
        //Methods
        size_type size() const {return chars.size() - 1;}
        const char* c_str() const {return chars.begin();} //Return a pointer to the actual string. Implementation since C++11.
        char* c_str() {return chars.begin();}
        const char* data() const {return chars.begin();} //Same behaviour as c_str()
        char* data() {return chars.begin();}
        bool empty() const {return !(chars.size() - 1);}
        size_type copy(char* dest, size_type count, size_type pos = 0) const { //Copies from string to char pointer. DOES NOT COPY null terminator!
            if (pos > this->size())
                throw std::out_of_range("pos outside of string range");
            count = std::min(count, this->size());
            std::copy(this->begin(), this->end(), dest);
            return count;
        }
        void clear() {chars.erase(begin(), end());} //Removes all characters (except for null term)
        template<class FwdIt>
        iterator erase(FwdIt first, FwdIt last) { //Removes all characters from [first, last)
            return chars.erase(first, last);
        }
        Str& append(size_type n, char c);
        Str& append( const Str& str );
        Str& append( const char* s );

        //Conversions
        // For boolean conversion, we no longer use void*. (C++11 idiom)
        // See:
        // https://stackoverflow.com/questions/32168971/why-operator-void-conversion-function-added-to-the-c-stream-classes/32169019
        // https://stackoverflow.com/questions/6242768/is-the-safe-bool-idiom-obsolete-in-c11
        explicit operator bool() const {
            return !(this->empty());
        };
    private:
        Vec<char> chars;
};

std::ostream& operator<<(std::ostream& os, const Str& s) {
    std::copy(s.begin(), s.end(), std::ostream_iterator<Str::value_type>(os));
    // for (Str::size_type i = 0; i != s.size(); ++i)
    //     os << s[i];
    return os;
}

std::istream& operator>>(std::istream& is, Str& s) { //TODO FIX
    char c; //char to input
    s.chars.clear();
    //Skip all initial whitespaces first
    while ((is >> c) && isspace(c))
        ;
    if (is) {
        do s.chars.push_back(c);
        while ((is.get(c)) && !isspace(c)); //We use .get() rather than >> as op>> will skip whitespaces
        s.chars.push_back('\0');
    }
    return is;
}
std::istream& getline(std::istream& is, Str& s) { // TODO
    char c; //char to input
    s.chars.clear();
    if (is) {
        while ((is.get(c)) && c != '\n') //We use .get() rather than >> as op>> will skip whitespaces
            s.chars.push_back(c);
        s.chars.push_back('\0');
    }
    return is;
}
// Append methods. Main way of adding stuff to Str
// Invariant: assumes that Str is already properly initialized (chars has \0 at the end)
Str& Str::append(size_type n, char c) {
    chars.pop_back(); //Remove \0
    for (size_type i = 0; i != n; i++) {
        chars.push_back(c);
    }
    chars.push_back('\0');
    return *this;
}
Str& Str::append( const Str& str ) {
    chars.pop_back();
    std::copy(str.begin(), str.end(), std::back_inserter(chars));
    chars.push_back('\0');
    return *this;
}
Str& Str::append( const char* c ) {
    chars.pop_back();
    std::copy(c, c + strlen(c), std::back_inserter(chars));
    chars.push_back('\0');
    return *this;
}
#endif