#include <iostream>

// Base class
class Base {
protected:
    int baseData;

public:
    Base(int data = 0) : baseData(data) {}

    virtual void print() const {
        std::cout << "Base class, baseData = " << baseData << "\n";
    }

    virtual ~Base() = default; // Virtual destructor for proper cleanup
};

// Derived class
class Derived : public Base {
private:
    int derivedData;

public:
    Derived(int baseData = 0, int derivedData = 0)
        : Base(baseData), derivedData(derivedData) {}

    void print() const override {
        std::cout << "Derived class, baseData = " << baseData
                  << ", derivedData = " << derivedData << "\n";
    }
};

// Function that causes slicing
void f(Base& b_) {
    auto b = b_;
    std::cout << "Inside function f:\n";
    b.print(); // This will call Base::print due to slicing
}

int main() {
    Derived d(10, 20); // baseData = 10, derivedData = 20
    std::cout << "Before calling f:\n";
    d.print(); // Calls Derived::print

    f(d); // Object slicing occurs here

    return 0;
}
