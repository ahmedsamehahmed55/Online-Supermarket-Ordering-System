#ifndef TVECTOR_H
#define TVECTOR_H

#include <iostream>

template <typename T>
class tvector {
private:
    T* _data;           // Pointer to the array of elements
    int _max;           // Maximum capacity of the array
    int _current;       // Current number of elements
    int _incrementby;   // Number of slots to expand by
    bool _sorted;       // Flag to indicate if vector is sorted

    // Expand the array by 'esize' slots
    int _expand(int esize);

    // Merge sort helper methods
    static void mergeSort(T arr[], const int size, bool (*compare)(const T&, const T&));
    static void merge(T leftarr[], T rightarr[], T arr[], int left, int right, bool (*compare)(const T&, const T&));
    static bool defaultCompare(const T& a, const T& b) {
        return a < b;
    }

public:
    tvector();               // Default constructor
    tvector(int init_size);  // Constructor with initial size
    ~tvector();              // Destructor

    // Set increment value
    int setIncrement(int inc);

    // Add elements
    int addToEnd(T& elem);       // Add element at the end
    int addToStart(T& elem);     // Add element at the start
    int addAt(T& elem, int loc); // Add element at a specific location

    // Remove elements
    T* removeFromEnd();      // Remove element from end
    T* removeFromStart();    // Remove element from start
    T* removeFrom(int loc);  // Remove element from specific location

    // Utility methods
    int contract();           // Reduce array size to current elements
    bool isSorted();          // Check if vector is sorted
    T* elemAt(int loc);       // Access element at a specific location
    int getCount();           // Get number of elements
    bool isEmpty();           // Check if vector is empty
    int freeSpace();          // Get remaining free space
    std::ostream& print(std::ostream& out); // Print vector

    // Sorting and searching
    void mergeSort(bool (*compare)(const T&, const T&)); // Merge sort with custom compare
    void mergeSort();                                   // Merge sort with default compare
    void insertInOrder(T& elem, bool ascending);       // Insert element maintaining order
    int search(T data);                                // Search for element (binary if sorted)
};


// ================= Default Constructors ================= //
template <class T>
tvector<T>::tvector() : _data(nullptr), _max(0), _current(0), _incrementby(20) {}

template <class T>
tvector<T>::tvector(int init_size) : _data(nullptr), _max(0), _current(0), _incrementby(20) {
    _expand(init_size);
}

// ================= Destructor ================= //
template <class T>
tvector<T>::~tvector() {
    delete[] _data;
}

// ================= isSorted ================= //
template <typename T>
bool tvector<T>::isSorted() {
    for (int i = 1; i < _current; i++) {
        if (_data[i] < _data[i - 1]) return false;
    }
    return true;
}

// ================= Element Access ================= //
template <class T>
T* tvector<T>::elemAt(int loc) {
    if (loc < 0 || loc > _current - 1) return nullptr;
    return &_data[loc];
}

// ================= Contract ================= //
template <class T>
int tvector<T>::contract() {
    if (_current == _max) return _max;

    T* newarr = new T[_current];
    for (int i = 0; i < _current; i++) newarr[i] = _data[i];

    delete[] _data;
    _data = newarr;
    _max = _current;
    return _max;
}

// ================= Set Increment ================= //
template <class T>
int tvector<T>::setIncrement(int inc) {
    if (inc > 0) _incrementby = inc;
    return _incrementby;
}

// ================= Expand ================= //
template <class T>
int tvector<T>::_expand(int esize) {
    if (esize < 1) return _max;

    int newmax = _max + esize;
    T* newarr = new T[newmax];

    for (int i = 0; i < _current; i++) newarr[i] = _data[i];

    delete[] _data;
    _data = newarr;
    _max = newmax;
    return _max;
}

// ================= Empty / Free Space ================= //
template <class T>
bool tvector<T>::isEmpty() {
    return (_current == 0);
}

template <class T>
int tvector<T>::freeSpace() {
    return _max - _current;
}

// ================= Print ================= //
template <class T>
std::ostream& tvector<T>::print(std::ostream& out) {
    out << "tvector: Max= " << _max << "     Free Space= " << freeSpace() << "\n\n";
    if (_current < 1) {
        out << "{}" << std::endl;
        return out;
    }

    out << "{ ";
    for (int i = 0; i < _current - 1; i++) out << _data[i] << ", ";
    out << _data[_current - 1] << " }" << std::endl;

    return out;
}

// ================= Add Methods ================= //
template <class T>
int tvector<T>::addToStart(T& elem) {
    return addAt(elem, 0);
}

template <class T>
int tvector<T>::addToEnd(T& elem) {
    return addAt(elem, _current);
}

template <class T>
int tvector<T>::addAt(T& elem, int loc) {
    if (loc < 0 || loc > _current) return -1;

    if (_current >= _max) _expand(_incrementby);

    for (int i = _current - 1; i >= loc; i--) _data[i + 1] = _data[i];

    _data[loc] = elem;
    _current++;

    return _current;
}

// ================= Remove Methods ================= //
template <class T>
T* tvector<T>::removeFromStart() {
    return removeFrom(0);
}

template <class T>
T* tvector<T>::removeFromEnd() {
    return removeFrom(_current - 1);
}

template <class T>
T* tvector<T>::removeFrom(int loc) {
    if (isEmpty() || loc < 0 || loc >= _current) return nullptr;

    T* removed = new T(_data[loc]);
    for (int i = loc; i < _current - 1; i++) _data[i] = _data[i + 1];
    _current--;

    return removed;
}

// ================= Sort Methods ================= //
template <typename T>
void tvector<T>::mergeSort(bool (*compare)(const T&, const T&)) {
    mergeSort(_data, _current, compare);
}

template <typename T>
void tvector<T>::mergeSort() {
    mergeSort(_data, _current, defaultCompare);
}

template <typename T>
void tvector<T>::mergeSort(T arr[], const int size, bool (*compare)(const T&, const T&)) {
    if (size <= 1) return;

    int left = size - size / 2;
    int right = size / 2;

    T* leftarr = new T[left];
    T* rightarr = new T[right];

    for (int i = 0; i < left; i++) leftarr[i] = arr[i];
    for (int j = 0; j < right; j++) rightarr[j] = arr[left + j];

    mergeSort(leftarr, left, compare);
    mergeSort(rightarr, right, compare);

    merge(leftarr, rightarr, arr, left, right, compare);

    delete[] leftarr;
    delete[] rightarr;
}

template <typename T>
void tvector<T>::merge(T leftarr[], T rightarr[], T arr[], int left, int right, bool (*compare)(const T&, const T&)) {
    int i = 0, j = 0, k = 0;

    while (i < left && j < right) {
        if (compare(leftarr[i], rightarr[j])) arr[k++] = leftarr[i++];
        else arr[k++] = rightarr[j++];
    }
    while (i < left) arr[k++] = leftarr[i++];
    while (j < right) arr[k++] = rightarr[j++];
}

// ================= Count / InsertInOrder / Search ================= //
template <typename T>
int tvector<T>::getCount() {
    return _current;
}

template <typename T>
void tvector<T>::insertInOrder(T& elem, bool ascending) {
    if (_current == 0) {
        addToStart(elem);
        return;
    }

    int pos = 0;
    while (pos < _current &&
           ((ascending && _data[pos] < elem) ||
            (!ascending && _data[pos] > elem))) {
        pos++;
    }

    addAt(elem, pos);
}

template <typename T>
int tvector<T>::search(T data) {
    if (isSorted()) { // binary search
        int left = 0, right = _current - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (_data[mid] == data) return mid;
            else if (_data[mid] < data) left = mid + 1;
            else right = mid - 1;
        }
    } else { // linear search
        for (int i = 0; i < _current; i++) {
            if (_data[i] == data) return i;
        }
    }
    return -1;
}

#endif
