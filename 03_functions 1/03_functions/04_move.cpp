#include <iostream>
#include <vector>
#include <utility> // For std::move

class X {
private:
    std::vector<int> data; // Large resource

public:
    // Constructor
    X(size_t size) : data(size, 0) {
        std::cout << "Constructed X with size " << size << "\n";
    }

    // Move Constructor
    X(X&& other) noexcept : data(std::move(other.data)) {
        std::cout << "Move Constructor called\n";
    }

    // Deleted Copy Constructor
    X(const X&) = delete;

    // Deleted Copy Assignment Operator
    X& operator=(const X&) = delete;

    // Move Assignment Operator
    X& operator=(X&& other) noexcept {
        if (this != &other) {
            data = std::move(other.data);
            std::cout << "Move Assignment Operator called\n";
        }
        return *this;
    }

    // Display size of data
    void show() const {
        std::cout << "X contains " << data.size() << " elements\n";
    }

    // Check if the object is empty (after being moved)
    bool is_empty() const {
        return data.empty();
    }
};

// Function that accepts an rvalue reference and explicitly transfers ownership
void f(X&& v_) {
    // Ownership transfer is done here.
    X v{std::move(v)};
    std::cout << "Function f is processing X...\n";
    v.show();
}

int main() {
    X x1(1000); // Create an instance of X

    // Transfer ownership to function f
    f(std::move(x1));


    std::cout << "\nAfter std::move:\n";
    if (x1.is_empty()) {
        std::cout << "x1 is now empty after being moved.\n";
    } else {
        std::cout << "x1 still contains elements.\n";
    }

    return 0;
}
