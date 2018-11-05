#ifndef GUARD_VEC_H
#define GUARD_VEC_H

#include <memory>   // For STL allocatator
#include <algorithm>
#include <cstddef>
#include <iostream>
#include <iterator> // ostream_iterator
#include <stdexcept> // out_of_range
// Vector implementation, similar to that in STL
// Chapter 11 - Accelerated C++
/* Basic operations to be supported
// construct a vector
vector<Student_info> vs; // empty vector
vector<double> v(100); // vector with 100 elements

// obtain the names of the types used by the vector
vector<Student_info>::const_iterator b, e;
vector<Student_info>::size_type i = 0;

// use size and the index operator to look at each element in the vector
for (i = 0; i != vs.size(); ++i)
cout << vs[i].name();
// return iterators positioned on the first and one past the last element
b = vs.begin(); e = vs.end();

// Insert elements
v.push_back(1.0);

TODO:
Range operator
erase, clear
Allocate directly from array of thingys
*/


template<class T>
class Vec {
    public:
        typedef T* iterator;
        typedef const T* const_iterator;
        typedef size_t size_type;
        typedef T value_type;

        //Constructors
        Vec() {create();};     //Default
        explicit Vec(size_type n, const T& val = T()) {create(n, val);} //Explicit
        Vec(std::initializer_list<T> list) { create(list.begin(), list.end()); }
        template<class FwdIt>
        Vec(FwdIt first, FwdIt last) { create(first, last);}
        friend void swap(Vec<T>& v1, Vec<T>& v2) { //swap interface
            using std::swap;

            //Swap data pointers
            swap(v1.data, v2.data);
            swap(v1.avail, v2.avail);
            swap(v1.limit, v2.limit);
        };    
        Vec(const Vec& v) { create(v.begin(), v.end());} //Initialization (Copy constructor)
        Vec& operator=(Vec);     //Assignment constructor
        ~Vec() {uncreate();}     //Destructor
        Vec(Vec&& v): Vec() {    //Move constructor with forwarding reference
            swap(*this, v);
        }

        //Operators
        // template<class T1>
        friend std::ostream& operator<<(std::ostream& os, const Vec<T>& v) {
            os << '[';
            std::copy(v.begin(), v.end(), std::ostream_iterator<T> (os, ", "));
            os << ']';
            return os;
        }

        //For testing
        friend int& operator+(int& lhs, const Vec<T>& v) {
            return ++lhs;
        }

        //Interfaces
        size_type size() const {return avail - data;}   //Cast from ptrdiff_t to size_type
        bool empty() const {return (!data || (data == avail));}
        T& operator[] (size_type i) {return data[i];}
        const T& operator[] (size_type i) const {return data[i];}   //Overloading works as there is a implicit parameter for all member functions (of the object it is operating on). It differs for const and non-const

        iterator begin() {return data;}
        const_iterator begin() const {return data;}
        iterator end() {return avail;}
        const_iterator end() const {return avail;}

        void push_back(const T& val) {
            if (avail == limit) //Get space if needed
                grow();
            unchecked_append(val);  //Append new element
        }
        void pop_back() { //Remove final element
            if (data != avail) {
                alloc.destroy(--avail);
                //Check if no more elements
                if (data == avail)
                    uncreate();
            }
        }
        iterator erase(const_iterator it); // Removes one element. Does not change capacity
        iterator erase(const_iterator first, const_iterator last); //Removes elements between [first, last)
        void clear() {erase(begin(), end());} //Removes all elements
    private:
        // std::unique_ptr<T> data;
        // std::unique_ptr<T> avail;
        // std::unique_ptr<T> limit;
        T* data;    //Ptr to start of data
        T* avail;   //Ptr to one past last data point
        T* limit;    //Ptr to last allocated space

        std::allocator<T> alloc; //Memory allocator

        void create(); //Primary method of constructing arrays
        void create(size_type, const T&);
        void create(const_iterator, const_iterator);

        void grow();    //For growing allocated size
        void unchecked_append(const T&);    //Append element to Vec without checking
        void uncreate();    //Removes all elements

        iterator nonconst_cast(const_iterator it) { //Cast iterator to non-const
            return begin() + (it - begin());
        }
};

/* Copies RHS to LHS, using copy-swap idiom */
template<class T>
Vec<T>& Vec<T>::operator=(Vec<T> rhs) {
    swap(*this, rhs);
    return *this;
}

/* Create assumes unallocated memory */
template<class T>
void Vec<T>::create() {
    data = avail = limit = nullptr;
}

template<class T>
void Vec<T>::create(size_type n, const T& val) {
    data = alloc.allocate(n);
    avail = limit = data + n;
    std::uninitialized_fill(data, avail, val);    
}

template<class T>
void Vec<T>::create(const_iterator first, const_iterator last) {
    data = alloc.allocate(last - first);
    avail = limit = std::uninitialized_copy(first, last, data);
}

//To double the size
template<class T>
void Vec<T>::grow() {
    size_type new_size = std::max(2*(limit - data), ptrdiff_t(1));

    //Allocate new space, and copy existing elements there first
    iterator new_data = alloc.allocate(new_size);
    iterator new_avail = std::uninitialized_copy(data, avail, new_data);

    //Return old space
    uncreate();

    //Change pointers to new aray
    data = new_data;
    avail = new_avail;
    limit = data + new_size;
}

template<class T>
void Vec<T>::unchecked_append(const T& val) {
    alloc.construct(avail++, val);
}

//Deletes all space
template<class T>
void Vec<T>::uncreate() {
    if (data) { //Check if empty first. Deallocate cannot take zero pointer
        //Destroy objects
        while (avail != data)
            alloc.destroy(--avail);

        //Deallocate memory
        alloc.deallocate(data, limit-data);

        //Reset pointers to indicate empty
        data = avail = limit = nullptr;
    }
}

template<class T>
typename Vec<T>::iterator Vec<T>::erase(const_iterator it) { //remove [first; last)
    if (it >= this->end())
        throw std::out_of_range("Iterator outside of range");
    //Swap from last onwards
    iterator dest = nonconst_cast(it);
    iterator first = dest + 1;
    while (first != this->end()) {
        *dest++ = std::move(*first++);
    }
    avail--;
    return dest; //const cast to non-const.
}

template<class T>
typename Vec<T>::iterator Vec<T>::erase(const_iterator first, const_iterator last) { //remove [first; last)
    if ((first > this->end()) || (last > this->end()))
        throw std::out_of_range("Iterator outside of range");
    //Swap from last onwards
    iterator dest = nonconst_cast(first);
    iterator right = nonconst_cast(last);
    while (right != this->end()) {
        *dest++ = std::move(*right++);
    }
    avail = dest;
    return nonconst_cast(last); //const cast to non-const.
}
#endif