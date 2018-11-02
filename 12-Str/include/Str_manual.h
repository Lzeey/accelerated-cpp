#ifndef GUARD_STR_H
#define GUARD_STR_H

#include <memory>
#include <algorithm>
#include <iterator> //back_inserter
#include <iostream>

/* Acclereated Cpp - Chapter 12. String class with manual memory allocation.
The implementation is awkward as there is no real way of supporting appending without preallocating a buffer.
i.e. Exactly like std::vector!
The naive way is to reallocate a new buffer, and copy the old memory to it, but this is terribly inefficient.

Thus, the implementation using Vec is efficient enough for our use-case.
*/
class Str {
    public:
        typedef size_t size_type;
        typedef char* iterator;
        typedef const char* const_iterator;

        // Constructors
        Str() { create(0, '\0');}    //Default constructor
        Str(const char* c) {create(c, c + std::strlen(c));}
        Str(size_type n, char c) {create(n, c);}
        template<class FwdIter> Str(FwdIter b, FwdIter e) {create(b, e);}

        // Operators
        char& operator[] (size_type i) {return chars[i];}
        const char& operator[] (size_type i) const {return chars[i];}
        Str& operator+=(const Str& s);
        Str operator+(const Str& s);
        friend std::ostream& operator<<(std::ostream&, const Str&);
        friend std::istream& operator>>(std::istream&, Str&);

        iterator begin() {return chars;}
        const_iterator begin() const {return chars;}
        iterator end() {return chars + length - 1;}
        const_iterator end() const {return chars + length - 1;}

        //Rule of five
        ~Str() {uncreate();}
        Str(const Str& s) { create(s.chars, s.chars + s.size()); }  //Copy
        Str& operator=(Str s) { //Assignment
            swap(*this, s);
            return *this;
        }
        friend void swap(Str&, Str&); //Swap
        Str(Str&& s): Str() { swap(*this, s);} //Move w/ forwarding reference.

        //Methods
        size_type size() const {return length - 1;}
        void append(const Str&);
        void append(const char*, const size_t);
        void prepend(const char*, const size_t);
        void append(const char);
        

    private:
        // chars is null-terminated. length contains total chars (including null).
        // valid length is length - 1
        iterator chars = nullptr;
        size_type length = 0;
        // std::allocator<char> alloc;

        void create(size_type, char);
        template<class FwdIt> void create(FwdIt, FwdIt);
        void uncreate();
};

std::ostream& operator<<(std::ostream& os, const Str& s) {
    for (Str::size_type i = 0; i != s.size() - 1; ++i)
        os << s[i];
    return os;
}

// TODO
std::istream& operator>>(std::istream& is, Str& s) {
    char c; //char to input
    while (is && is.get(c) && std::isspace(c)); //Nothing to do
    if (is) //TODO
    return is;
}

void Str::create(size_type n, char c) {
    chars = new char[n + 1];
    for (size_type i; i != n; i++)
        chars[i] = c;
    chars[n + 1] = '\0';
    length = n + 1;
}

template<class FwdIt> 
void Str::create(FwdIt b, FwdIt e) {
    length = e - b + 1; //Extra character for null terminated
    chars = new char[length];
    memcpy(chars, b, length-1);
    d[length - 1] = '\0';
}

void Str::uncreate() {
    if (length != 0) {
        delete [] chars;
    }
    length = 0;
}

void swap(Str& s1, Str& s2) {
    using std::swap;

    swap(s1.chars, s2.chars);
    swap(s1.length, s2.length);
}
#endif