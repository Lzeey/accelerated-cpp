#ifndef GUARD_ZALGO_H
#define GUARD_ZALGO_H

#include <utility>

// class algorithm_z {
//     template<class In, class Out>
//     void copy(class In, class In, class Out);
// }

/* Exercise 8.2 in Acclerated Cpp
Reimplementation of STL's <algorithm> library */
//copy
namespace zalgo {
    //equals - Takes two input iterators
    /* 1,3) Returns true if the range [first1, last1) is equal to the range 
    [first2, first2 + (last1 - first1)), and false otherwise */
    template<class InIter1, class InIter2>
    bool equal(InIter1 first1, InIter1 last1, InIter2 first2) {
        while (first1 != last1 && *first1 == *first2) {
            first1++; first2++;
        }
        return first1 == last1;
    }

    //search
    /*1-4) Searches for the first occurrence of the subsequence of elements 
    [s_first, s_last) in the range [first, last - (s_last - s_first)). 
    Return Value:
    1-4) Iterator to the beginning of first subsequence [s_first, s_last) 
    in the range [first, last - (s_last - s_first)). If no such subsequence is found, last is returned.
    If [s_first, s_last) is empty, first is returned. (since C++11)*/
    template<class FwdIt1, class FwdIt2>
    FwdIt1 search(FwdIt1 first, FwdIt1 last, FwdIt2 s_first, FwdIt2 s_last) {
        for (;; ++first) {
            FwdIt1 it = first;
            for (FwdIt2 s_it = s_first; ;++s_it, ++it) {
                if (s_it == s_last) { //Found sequence
                    return first;
                } else if (it == last) { //End of main search element
                    return last;
                } else if (!(*it == *s_it)) { //Check equality
                    break;
                }
            }
        }
        return last;
    }

    //find
    template <class InIt, class T>
    InIt find(InIt first, InIt last, const T& val) {
        while (first != last && *first != val)
            ++first;
        return first;
    }

    //find_if
    template <class InIt, class UnaryPredicate>
    InIt find_if(InIt first, InIt last, UnaryPredicate p) {
        while (first != last && !p(*first))
            ++first;
        return first;
    }

    //find_if_not
    template <class InIt, class UnaryPredicate>
    InIt find_if_not(InIt first, InIt last, UnaryPredicate p) {
        while (first != last && p(*first))
            ++first;
        return first;
    }

    template<class InIt, class OutIt>
    void copy(InIt first, InIt last, OutIt dest) {
        while (first != last) {
            *dest++ = *first++;
        }
    }

    //remove_copy
    /* Copies elements from the range [first, last), to another range beginning at d_first, 
    omitting the elements which satisfy specific criteria. Source and destination ranges cannot overlap.*/
    template<class InIt, class OutIt, class T>
    void remove_copy(InIt first, InIt last, OutIt dest, const T& val) {
        while (first != last) {
            if (*first != val)
                *dest++ = *first;
            ++first;
        }
    }

    //remove_copy_if
    template<class InIt, class OutIt, class UnaryPredicate>
    void remove_copy_if(InIt first, InIt last, OutIt dest, UnaryPredicate p) {
        while (first != last) {
            if (!(p(*first)))
                *dest++ = *first;
            ++first;
        }
    }

    //remove
    /* Removes all elements satisfying specific criteria from the range [first, last) 
    and returns a past-the-end iterator for the new end of the range. */
    template< class FwdIt, class T >
    FwdIt remove(FwdIt first, FwdIt last, const T& value ) {
        //Requires implementation of move?
        first = zalgo::find(first, last, value);
        if (first != last) {
            for (FwdIt it = first; it != last; ++it) {
                if (!(*it == value)) //Keep value
                    *first++ = std::move(*it); // Check what std move does.
            }
        }
        return first;
    }

    //transform
    // std::transform applies the given function to a range and stores the result in another range, beginning at d_first.
    template <class InIt, class OutIt, class UnaryOperation>
    OutIt transform(InIt first, InIt last, OutIt d_first, UnaryOperation unary_op) {
        while (first != last) {
            *d_first++ = unary_op(*first++);
        }
        return d_first;
    }

    //partition
    /* 1) Reorders the elements in the range [first, last) 
    in such a way that all elements for which the predicate p returns true 
    precede the elements for which predicate p returns false. 
    Relative order of the elements is not preserved. 
    Returns iterator to the start of second group */
    template< class FwdIt, class UnaryPredicate >
    FwdIt partition( FwdIt first, FwdIt last, UnaryPredicate p) {
        first = zalgo::find_if_not(first, last, p);
        // invariant: all before first satisfies predicate p
        for (FwdIt it = first; it != last; ++it) {
            if (p(*it)) {
                //Swap first and it value
                std::swap(*first, *it);
                ++first;
            }
        }
        return first;
    }
    //accumulate
    /* Computes the sum of the given value init and the elements in the range [first, last). 
    The first version uses operator+ to sum up the elements, the second version uses the given 
    binary function op, both applying std::move to their operands on the left hand side (since C++20). */
    template <class InIt, class T>
    T accumulate(InIt first, InIt last, T init) {
        while (first != last) {
            // init += *first++;
            init = std::move(init) + *first++;
        }
        return init;
    }

    //replace
    template< class ForwardIt, class T >
    void replace( ForwardIt first, ForwardIt last, const T& old_value, const T& new_value ) {
        while (first != last) {
            if (*first == old_value)
                *first = new_value;
            ++first;
        }
    }

    //reverse
    template<class BiIt>
    void reverse(BiIt first, BiIt last) {
        while (first != last) {
            --last;
            if (first != last)
                std::swap(*first++, *last);
        }
    }



}
//find
//template<class In, class Out> //Input and output iterators


//find_if



#endif