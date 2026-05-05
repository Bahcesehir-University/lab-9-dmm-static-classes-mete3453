// ============================================================
// Lab: Dynamic Memory Management & Static Classes
// Course: Object-Oriented Programming for Engineers
// Level: 2nd Year Engineering
// Duration: 50 minutes
// ============================================================
// This file contains ALL code for this lab.
// Do NOT create any .h files. Everything stays here.
// ============================================================

#include <iostream>
#include <string>
#include <cstring>

using namespace std;

// ================================================================
// CLASS DEFINITIONS
// ================================================================

// -------------------------------------------------
// Class: IntArray
// -------------------------------------------------
class IntArray {
private:
    int* data;
    int capacity;
    int count;

public:
    IntArray(int cap);
    ~IntArray();
    IntArray(const IntArray& other);
    IntArray& operator=(const IntArray& other);

    bool add(int value);
    int get(int index) const;
    int size() const;
    int getCapacity() const;
    bool isEmpty() const;
    bool removeLast();
};

// -------------------------------------------------
// Class: Tracker
// -------------------------------------------------
class Tracker {
private:
    static int objectCount;
    Tracker() = delete;

public:
    static void objectCreated();
    static void objectDestroyed();
    static int getActiveCount();
    static void resetCount();
};

// ================================================================
// STATIC MEMBER INITIALIZATION
// ================================================================

int Tracker::objectCount = 0;

// ================================================================
// TRACKER IMPLEMENTATION
// ================================================================

void Tracker::objectCreated() {
    objectCount++;
}

void Tracker::objectDestroyed() {
    objectCount--;
}

int Tracker::getActiveCount() {
    return objectCount;
}

void Tracker::resetCount() {
    objectCount = 0;
}

// ================================================================
// INTARRAY IMPLEMENTATION
// ================================================================

IntArray::IntArray(int cap) {
    data = new int[cap];
    capacity = cap;
    count = 0;
    Tracker::objectCreated();
}

IntArray::~IntArray() {
    delete[] data;
    Tracker::objectDestroyed();
}

IntArray::IntArray(const IntArray& other) {
    capacity = other.capacity;
    count = other.count;
    data = new int[capacity];

    for (int i = 0; i < count; i++) {
        data[i] = other.data[i];
    }

    Tracker::objectCreated();
}

IntArray& IntArray::operator=(const IntArray& other) {
    if (this != &other) {
        delete[] data;

        capacity = other.capacity;
        count = other.count;
        data = new int[capacity];

        for (int i = 0; i < count; i++) {
            data[i] = other.data[i];
        }
    }
    return *this;
}

bool IntArray::add(int value) {
    if (count < capacity) {
        data[count++] = value;
        return true;
    }
    return false;
}

int IntArray::get(int index) const {
    if (index >= 0 && index < count) {
        return data[index];
    }
    return -1;
}

int IntArray::size() const {
    return count;
}

int IntArray::getCapacity() const {
    return capacity;
}

bool IntArray::isEmpty() const {
    return count == 0;
}

bool IntArray::removeLast() {
    if (!isEmpty()) {
        count--;
        return true;
    }
    return false;
}

// ================================================================
// MAIN
// ================================================================

int main() {
    cout << "=== Dynamic Memory & Static Classes Lab ===" << endl << endl;

    cout << "[1] Creating IntArray with capacity 5..." << endl;
    IntArray arr(5);
    cout << "    Active objects: " << Tracker::getActiveCount() << endl;

    cout << "[2] Adding elements: 10, 20, 30" << endl;
    arr.add(10);
    arr.add(20);
    arr.add(30);
    cout << "    Size: " << arr.size()
         << ", Capacity: " << arr.getCapacity() << endl;

    cout << "[3] Elements: ";
    for (int i = 0; i < arr.size(); i++) {
        cout << arr.get(i) << " ";
    }
    cout << endl;

    cout << "[4] Copy constructing arr2 from arr..." << endl;
    IntArray arr2(arr);
    cout << "    Active objects: " << Tracker::getActiveCount() << endl;
    cout << "    arr2 size: " << arr2.size() << endl;

    cout << "[5] Creating arr3(2), then assigning arr to arr3..." << endl;
    IntArray arr3(2);
    cout << "    Active objects: " << Tracker::getActiveCount() << endl;
    arr3 = arr;
    cout << "    arr3 size after assignment: " << arr3.size() << endl;

    cout << "[6] Removing last from arr..." << endl;
    arr.removeLast();
    cout << "    arr size after removeLast: " << arr.size() << endl;

    cout << "[7] Testing scope-based destruction..." << endl;
    {
        IntArray temp(3);
        temp.add(99);
        cout << "    Inside scope - Active objects: "
             << Tracker::getActiveCount() << endl;
    }
    cout << "    After scope  - Active objects: "
         << Tracker::getActiveCount() << endl;

    cout << endl << "=== Lab Complete ===" << endl;
    return 0;
}
