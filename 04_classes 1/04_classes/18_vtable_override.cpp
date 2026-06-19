#include <iostream>
#include <memory> // For std::unique_ptr
#include <cstring> // For memset

class Base {
public:
    virtual void display() const {
        std::cout << "Base::display()\n";
    }
    virtual ~Base() = default; // Virtual destructor ensures proper cleanup
};

class Derived : public Base {
public:
    void display() const override {
        std::cout << "Derived::display()\n";
    }
};

void init(Base& obj) {
    // Improperly clear memory using memset, overwriting vtable
    std::memset(&obj, 0, sizeof(obj)); // Undefined behavior
}

int main() {
    // Use unique_ptr to manage the Derived object
    std::unique_ptr<Base> ptr = std::make_unique<Derived>();

    std::cout << "Before memset:\n";
    ptr->display(); // Works fine, calls Derived::display()

    std::cout << "\nApplying memset:\n";
    init(*ptr); // Overwrites the vtable pointer

    std::cout << "\nAfter memset:\n";
    try {
        ptr->display(); // Undefined behavior, vtable is broken
    } catch (...) {
        std::cout << "Exception caught! Vtable is broken.\n";
    }

    return 0;
}
