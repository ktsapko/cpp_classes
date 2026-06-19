#include <iostream>
#include <memory>

// Bad Example: Calling a virtual function in the constructor
class MyClassBad {
public:
    MyClassBad() {
        std::cout << "MyClassBad Constructor\n";
        f(); // Virtual call inside constructor (undefined behavior)
    }

    virtual void f() = 0; // Pure virtual function
    virtual ~MyClassBad() = default; // Virtual destructor
};

class DerivedBad : public MyClassBad {
public:
    void f() override {
        std::cout << "DerivedBad::f() called\n";
    }
};

// Good Example: Using a factory method with an init() function
class MyClassGood {
public:
    MyClassGood() {
        std::cout << "MyClassGood Constructor\n";
    }

    virtual void init() = 0; // Virtual function for initialization

    virtual ~MyClassGood() = default;

    template <typename T>
    static std::shared_ptr<T> create() {
        auto p = std::make_shared<T>();
        p->init(); // Virtual function is safely called after construction
        return p;
    }
};

class DerivedGood : public MyClassGood {
public:
    void init() override {
        std::cout << "DerivedGood::init() called\n";
    }
};

int main() {
    std::cout << "Bad Example:\n";
    try {
        // This will lead to undefined behavior
        DerivedBad badObj; // Calls MyClassBad constructor
    } catch (...) {
        std::cout << "Caught exception in bad example.\n";
    }

    std::cout << "\nGood Example:\n";
    // This safely constructs and initializes the object
    auto goodObj = MyClassGood::create<DerivedGood>();
    return 0;
}
