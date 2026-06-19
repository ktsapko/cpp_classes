#include <iostream>

// Example of the Problem: Using protected data
class BaseProblem {
protected:
    int value = 0; // Protected data, accessible by derived classes
};

class DerivedProblem : public BaseProblem {
public:
    void increment() {
        value++; // Directly modifies base class's internal state
    }

    void printValue() const {
        std::cout << "Value (Problem): " << value << "\n";
    }
};

// Better Alternative: Using private data with accessors
class BaseBetter {
private:
    int value = 0; // Keep private to maintain encapsulation

protected:
    void setValue(int v) { value = v; }   // Provide controlled access
    int getValue() const { return value; }
};

class DerivedBetter : public BaseBetter {
public:
    void increment() {
        setValue(getValue() + 1); // Access via controlled interface
    }

    void printValue() const {
        std::cout << "Value (Better): " << getValue() << "\n";
    }
};

int main() {
    // Problematic Example
    DerivedProblem dp;
    dp.increment(); // Increments value directly
    dp.printValue();

    // Better Example
    DerivedBetter db;
    db.increment(); // Increments value via controlled interface
    db.printValue();

    return 0;
}
