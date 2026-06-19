#include <iostream>
#include <memory>

// Bad Example: Class with const and reference data members
class MyClassBad {
    const int i;  // Const data member
    int& j;       // Reference data member

public:
    MyClassBad(int value, int& ref) : i(value), j(ref) {}

    // Copy constructor
    MyClassBad(const MyClassBad& other) : i(other.i), j(other.j) {}

    // Copy assignment operator (Deleted due to const and reference members)
    MyClassBad& operator=(const MyClassBad& other) = delete;

    void print() const {
        std::cout << "MyClassBad: i = " << i << ", j = " << j << "\n";
    }
};

// Good Example: Class using smart pointers instead of const and references
class MyClassGood {
    std::unique_ptr<int> i; // Pointer to mimic "const-like" behavior
    int* j;                 // Raw pointer to mimic reference

public:
    MyClassGood(int value, int& ref) : i(std::make_unique<int>(value)), j(&ref) {}

    // Copy constructor
    MyClassGood(const MyClassGood& other) : i(std::make_unique<int>(*other.i)), j(other.j) {}

    // Copy assignment operator
    MyClassGood& operator=(const MyClassGood& other) {
        if (this != &other) {
            i = std::make_unique<int>(*other.i); // Deep copy
            j = other.j; // Copy pointer
        }
        return *this;
    }

    void print() const {
        std::cout << "MyClassGood: i = " << *i << ", j = " << *j << "\n";
    }
};

int main() {
    int shared_value = 10;

    // Bad Example
    MyClassBad bad1(5, shared_value);
    MyClassBad bad2 = bad1; // Copy constructor works
    // bad2 = bad1; // Uncommenting this will cause a compilation error

    bad1.print();
    bad2.print();

    // Good Example
    MyClassGood good1(5, shared_value);
    MyClassGood good2 = good1; // Copy constructor works
    good2 = good1;             // Copy assignment operator also works

    good1.print();
    good2.print();

    return 0;
}
