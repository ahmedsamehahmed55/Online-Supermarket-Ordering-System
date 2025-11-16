#ifndef TLIST_H
#define TLIST_H

#include<iostream>

// ==================== tlist Class ====================
// A template-based singly linked list that supports 
// dynamic storage of any data type T
template<typename T>
class tlist {
private:
    // ========== Node Class ==========
    class node {
    public:
        T _data;       // data stored in the node
        node* next;    // pointer to the next node
    };

    node* _head;       // pointer to the first node of the list
    int _count;        // number of elements currently in the list

    // Private setter for _count to manage it internally
    int setCount(const int); 

public:
    // ========== Constructors & Destructor ==========
    tlist();                     // default constructor
    tlist(const tlist<T>& other); // copy constructor
    ~tlist();                     // destructor

    // ========== Basic operations ==========
    int getCount();           // get number of elements
    bool isEmpty();           // check if list is empty
    void clear();             // delete all elements

    // ========== Add Methods ==========
    void addToBegining(const T&);   // insert at head
    void addToEnd(const T&);        // insert at end
    void addAt(int loc, const T&);  // insert at specific loc

    // ========== Remove Methods ==========
    T removeFromBegining();        // remove first element
    void removeFromLoc(int loc);   // remove element at index
    void removeFromEnd();          // remove last element
    void removeByPointer(const T* addressToRemove); // remove using pointer

    // ========== Find / Access ==========
    T findAt(int loc);             // get element at index

    // ========== Sorting ==========
    void sort();                   // bubble sort
    void insertInOrder(T& data);   // insert maintaining sorted order

    // ========== Search ==========
    T* search(T& data);            // linear search returning pointer

    // ========== Concatenation ==========
    void concatenate(tlist<T>& otherList); // append another list

    // ========== Printing ==========
    friend std::ostream& operator<<(std::ostream& out, const tlist<T>& list) {
        typename tlist<T>::node* temp = list._head;
        out << "tlist: length<" << list._count << "> {";
        while (temp) {
            out << temp->_data;
            if (temp->next) out << ", ";
            temp = temp->next;
        }
        out << "}" << std::endl;
        return out;
    }
};

// ==================== Constructors ====================

// Default constructor initializes an empty list
template<typename T>
tlist<T>::tlist(): _head(NULL), _count(0) {}

// Copy constructor: deep copies another list
template <typename T>
tlist<T>::tlist(const tlist<T>& other): _head(NULL), _count(0) {
    if (other._head == NULL) return;

    this->_head = new node;
    this->_head->_data = other._head->_data;
    this->_head->next = nullptr;

    node* current = _head;
    node* otherCurrent = other._head->next;
    while (otherCurrent != nullptr) {
        current->next = new node;
        current = current->next;
        current->_data = otherCurrent->_data;
        otherCurrent = otherCurrent->next;
    }
    current->next = nullptr;
    this->_count = other._count;
}

// Destructor clears the list
template<typename T>
tlist<T>::~tlist() {
    clear();
}

// ==================== Clear List ====================
template<typename T>
void tlist<T>::clear() {
    node* current = _head;
    node* NextNode = nullptr;

    while (current != nullptr) {
        NextNode = current->next;
        delete current;
        current = NextNode;
    }

    _head = nullptr;
    setCount(0);
}

// ==================== Add Methods ====================
template<typename T>
void tlist<T>::addToBegining(const T& data) {
    node* newNode = new node;
    newNode->_data = data;
    newNode->next = _head;
    _head = newNode;
    setCount(getCount() + 1);
}

template <typename T>
void tlist<T>::addToEnd(const T& newData) {
    if (_head == nullptr) { addToBegining(newData); return; }

    node* temp = _head;
    while (temp->next != nullptr) temp = temp->next;

    temp->next = new node;
    temp = temp->next;
    temp->_data = newData;
    temp->next = nullptr;
    setCount(getCount() + 1);
}

template<typename T>
void tlist<T>::addAt(int loc, const T& newData) {
    if (loc > getCount() || loc < 0) return; // validate
    else if (loc == getCount()) { addToEnd(newData); return; }
    else if (loc == 0) { addToBegining(newData); return; }

    node* temp = _head;
    for (int i = 0; i < loc - 1; i++) temp = temp->next;

    node* newNode = new node;
    newNode->next = temp->next;
    temp->next = newNode;
    newNode->_data = newData;
    setCount(getCount() + 1);
}

// ==================== Remove Methods ====================
template<typename T>
T tlist<T>::removeFromBegining() {
    if (_head == nullptr) return -1; // assumes T supports -1
    node* temp = _head;
    T data = _head->_data;
    _head = _head->next;
    delete temp;
    setCount(getCount() - 1);
    return data;
}

template<typename T>
void tlist<T>::removeFromEnd() {
    if (_head == nullptr) return;
    if (getCount() == 1) { removeFromBegining(); return; }

    node* temp = _head;
    for (int i = 0; i < getCount() - 2; i++) temp = temp->next;

    node* rmv = temp->next;
    temp->next = nullptr;
    delete rmv;
    setCount(getCount() - 1);
}

template<typename T>
void tlist<T>::removeFromLoc(int loc) {
    if (loc >= getCount()) return;
    if (loc == 0) { removeFromBegining(); return; }
    if (loc == getCount() - 1) { removeFromEnd(); return; }

    node* temp = _head;
    for (int i = 0; i < loc - 1; i++) temp = temp->next;

    node* rmv = temp->next;
    temp->next = rmv->next;
    delete rmv;
    setCount(getCount() - 1);
}

// ==================== Access Methods ====================
template<typename T>
T tlist<T>::findAt(int loc) {
    if (loc >= getCount() || loc < 0) {
        std::cerr << "Error: index out of range" << std::endl;
        exit(1);
    }
    node* temp = _head;
    for (int i = 0; i < loc; i++) temp = temp->next;
    return temp->_data;
}

// ==================== Count Management ====================
template<typename T>
int tlist<T>::setCount(const int num) {
    if (num < 0) return -1;
    _count = num;
    return _count;
}

template<typename T>
int tlist<T>::getCount() { return _count; }

// ==================== Utility ====================
template<typename T>
bool tlist<T>::isEmpty() { return _head == nullptr; }

template<typename T>
void tlist<T>::concatenate(tlist<T>& otherList) {
    if (_head == nullptr) { _head = otherList._head; setCount(otherList.getCount()); return; }
    node* temp = _head;
    while (temp->next != nullptr) temp = temp->next;
    temp->next = otherList._head;
    setCount(getCount() + otherList.getCount());
}

// ==================== Sorting / Search ====================
template<typename T>
void tlist<T>::insertInOrder(T& data) {
    if (isEmpty()) { addToEnd(data); return; }
    for (int i = 0; i < getCount(); i++) {
        if (data <= findAt(i)) { addAt(i, data); return; }
    }
    addToEnd(data);
}

template<typename T>
void tlist<T>::sort() {
    bool swapped = true;
    while (swapped) {
        swapped = false;
        node* temp = _head;
        while (temp->next != nullptr) {
            if (temp->_data > temp->next->_data) {
                T t = temp->_data;
                temp->_data = temp->next->_data;
                temp->next->_data = t;
                swapped = true;
            }
            temp = temp->next;
        }
    }
}

// Linear search: returns pointer to data if found
template<typename T>
T* tlist<T>::search(T& data) {
    node* temp = _head;
    while (temp != nullptr) {
        if (temp->_data == data) return &(temp->_data);
        temp = temp->next;
    }
    return nullptr;
}

// Remove node by pointer address
template<typename T>
void tlist<T>::removeByPointer(const T* addressToRemove) {
    node* temp = _head;
    node* prev = nullptr;

    if (temp == nullptr) return;

    while (temp != nullptr && &(temp->_data) != addressToRemove) {
        prev = temp;
        temp = temp->next;
    }

    if (prev == nullptr) _head = temp->next; // head node
    else prev->next = temp->next;            // middle or end

    delete temp;
    _count--;
}

#endif
