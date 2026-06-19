#include <iostream>
#include <utility> // For std::swap

class MyClass {
private:
    int value;

public:
    // Constructor
    MyClass(int v) : value(v) {}

    // Copy Constructor
    MyClass(const MyClass& other) : value(other.value) {
        std::cout << "Copy Constructor called\n";
    }

    // Move Constructor
    MyClass(MyClass&& other) noexcept : value(other.value) {
        other.value = 0; // Reset the source
        std::cout << "Move Constructor called\n";
    }

    // Swap Function
    friend void swap(MyClass& a, MyClass& b) noexcept {
        std::swap(a.value, b.value); // Use std::swap for the member
        std::cout << "swap() called\n";
    }

    // Print Function
    void print() const {
        std::cout << "MyClass value: " << value << "\n";
    }
};

int main() {
    MyClass obj1(10), obj2(20);

    std::cout << "Before swap:\n";
    obj1.print();
    obj2.print();

    swap(obj1, obj2);

    std::cout << "After swap:\n";
    obj1.print();
    obj2.print();

    return 0;
}
