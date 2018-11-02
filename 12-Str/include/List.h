#ifndef GUARD_LIST_H
#define GUARD_LIST_H

#include <memory>   // For STL allocatator
#include <algorithm>
#include <iterator> // back_inserter
#include <cassert>
#include <cstddef>

/* List implementation. Similar to that in std::list.
This implementation uses a double-linked list.
Interfaces
*/
template<class T>
class Node {
    public:
        T data;
        Node *next = nullptr;
        Node *prev = nullptr;

        //Constructor
        Node() = default;      //Default constructor
        explicit Node(const T& val): data(val) {};    //Explicit constructor
};

//Wrapper around Node to achieve compliance with Bidirectional iterators
//Enables ++ -- and all sorts of operators
template<class T> class List;
template<class T> class nodeiter;
template<class T>
class const_nodeiter {
    public:
        const_nodeiter() = default;
        T operator*() {return node->data;}
        T* operator->() {return &(node->data);}
        const_nodeiter operator++() {node = node->next; return *this;}
        const_nodeiter operator--() {node = node->prev; return *this;}
        const_nodeiter operator++(int) {const_nodeiter ret=*this; node = node->next; return ret;}
        const_nodeiter operator--(int) {const_nodeiter ret=*this; node = node->prev; return ret;}
        bool operator==(const_nodeiter rhs) const {return node==rhs.node;}
        bool operator!=(const_nodeiter rhs) const {return node!=rhs.node;}

    private:
        Node<T> *node = nullptr;
        const_nodeiter(Node<T>* i): node(i) {}

    friend class List<T>;
    friend class nodeiter<T>;
};

template<class T>
class nodeiter {
    public:
        typedef T value_type;
        nodeiter() = default;
        T& operator*() {return node->data;}
        T* operator->() {return &(node->data);}
        nodeiter operator++() {node = node->next; return *this;}
        nodeiter operator--() {node = node->prev; return *this;}
        nodeiter operator++(int) {nodeiter ret=*this; node = node->next; return ret;}
        nodeiter operator--(int) {nodeiter ret=*this; node = node->prev; return ret;}
        bool operator==(nodeiter rhs) const {return node==rhs.node;}
        bool operator!=(nodeiter rhs) const {return node!=rhs.node;}
        operator const_nodeiter<T>() {return {node};} //What is this???

    private:
        Node<T> *node = nullptr;
        nodeiter(Node<T>* i): node(i) {}

    friend class List<T>;
};

/* Main class*/
template<class T>
class List {
    public:
        //TODO: Write classes for iterators
        typedef nodeiter<T> iterator;
        typedef const_nodeiter<T> const_iterator;
        typedef size_t size_type;
        typedef T value_type;

        //Iterators
        iterator begin() {return iterator(head->next);}
        const_iterator begin() const {return const_iterator(head->next);}

        iterator end() {return iterator(tail);}
        const_iterator end() const {return const_iterator(tail);}

        //Constructors
        List() {create();}
        explicit List(size_type n, const T& val = T()) {create(n, val);} //Explicit
        
        friend void swap(List<T>&, List<T>&);    //swap interface
        List(const List& ls) { create(ls.begin(), ls.end());} //Initialization (Copy constructor)
        List& operator=(List);     //Assignment constructor
        ~List();                   //Destructor
        List(List&& v): List() {   //Move constructor with forwarding reference
            swap(*this, v);
        }

        //Interfaces
        size_type size() const {return _size;}   //Cast from ptrdiff_t to size_type
        bool empty() const {return (head->next == tail);}

        iterator insert(iterator pos, const T&); //Insert before pos. Can be end().
        iterator insert(const_iterator pos, const T&) const;
        void push_back(const T&);
        void push_front(const T&);
        iterator erase(iterator pos);
        iterator erase(const_iterator pos);

        //Operators (wo assignment)
        bool operator==(const List&);


    private:
        Node<T> *head = new Node<T>();    //Ptr to One before start of data. We use pointers so we can implement efficient swap.
        Node<T> *tail = new Node<T>();   //Ptr to One past last valid data
        size_type _size = 0;    //Internal storage for size
        //std::allocator<T> alloc; //Memory allocator

        void create(); //Primary method of constructing lists
        void create(size_type, const T&);
        void create(const_iterator, const_iterator);
};

/* Copies RHS to LHS, using copy-swap idiom */
template<class T>
List<T>& List<T>::operator=(List rhs) {
    swap(*this, rhs);
    return *this;
};

/* Swap method */
template<class T>
void swap(List<T>& ls1, List<T>& ls2) {
    using std::swap;

    //Swap data pointers
    swap(ls1.head, ls2.head);
    swap(ls1.tail, ls2.tail);
    swap(ls1._size, ls2._size);
}

//Destructor
template<class T>
List<T>::~List<T>() {
    iterator it = iterator(head->next);
    while (it != tail) {
        delete (it++).node;
    }

    //head->next = tail->prev = nullptr; //Indicate that list is empty
    delete head; delete tail;
    _size = 0;
}

template<class T>
typename List<T>::iterator List<T>::insert(iterator pos, const T& val) {
    Node<T> *newnode = new Node<T>(val);
    Node<T> *cur_node = pos.node;
    Node<T> *prev_node = cur_node->prev;
    prev_node->next = newnode;
    newnode->prev = prev_node;
    newnode->next = cur_node;
    cur_node->prev = newnode;
    ++_size;
    return iterator(newnode);
}

template<class T>
typename List<T>::iterator List<T>::insert(const_iterator pos, const T& val) const {
    Node<T> *newnode = new Node<T>(val);
    Node<T> *cur_node = pos->node;
    Node<T> *prev_node = cur_node->prev;
    prev_node->next = newnode;
    newnode->prev = prev_node;
    newnode->next = cur_node;
    cur_node->prev = newnode;
    ++_size;
    return iterator(newnode);
}

template<class T>
void List<T>::push_back(const T& val) {
    insert(end(), val);
}

template<class T>
void List<T>::push_front(const T& val) {
    insert(begin(), val);
}

template<class T>
typename List<T>::iterator List<T>::erase(iterator pos) {
    assert(pos != head && pos != tail);
    //Grab the next and previous node
    Node<T> *cur_node = pos.node;
    Node<T> *next = cur_node->next, *prev = cur_node->prev;
    next->prev = prev;
    prev->next = next;

    delete cur_node;
    --_size;
    return iterator(next);
}

template<class T>
typename List<T>::iterator List<T>::erase(const_iterator pos) {
    assert(pos != head && pos != tail);
    //Grab the next and previous node
    Node<T>* cur_node = pos.node;
    Node<T>* next = cur_node->next, prev = cur_node->prev;
    next->prev = prev;
    prev->next = next;

    delete cur_node; 
    --_size;
    return const_iterator(next);
}

// Private methods for List ----------------
/* Create is the underlying method for initializing Nodes. */
template<class T>
void List<T>::create() {
    //Rely on default constructor for the rest.
    head->next = tail;
    tail->prev = head;
}

//Initialize Nodes on the heap with heap with 'new'
// Use naive for-loop. Any better than this?
template<class T>
void List<T>::create(size_type n, const T& val) {
    //Is this exception safe??
    Node<T> *prev_node = head;
    for (auto i = 0; i != n; i++) {
        Node<T> *cur_node = new Node<T>(val);
        prev_node->next = cur_node;
        cur_node->prev = prev_node;

        prev_node = cur_node;
    }
        
    prev_node->next = tail;
    tail->prev = prev_node;

    //Update _size
    _size = n;
}

template<class T>
void List<T>::create(const_iterator first, const_iterator last) {
    create();
    std::copy(first, last, std::back_inserter(*this));
}

//Operators
// template<class T> //TODO: FIX
// bool List<T>::operator==(const List& oth) {
//     return std::equal(begin(), end(), oth.begin());
// };

#endif