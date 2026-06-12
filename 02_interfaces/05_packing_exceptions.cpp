#include <iostream>
#include <tuple> // For std::tuple

// Golang language implements this system

// Function that returns a value and an error code
std::tuple<int, bool> do_something(bool success) {
    if (success) {
        return {42, false}; // {value, no error}
    } else {
        return {0, true};   // {no value, error occurred}
    }
}

int main() {
    // Simulate a successful operation
    auto [value, error_code] = do_something(true);
    if (error_code) {
        std::cerr << "Error: Operation failed\n";
    } else {
        std::cout << "Success: Value = " << value << '\n';
    }

    // Simulate a failed operation
    auto [value2, error_code2] = do_something(false);
    if (error_code2) {
        std::cerr << "Error: Operation failed\n";
    } else {
        std::cout << "Success: Value = " << value2 << '\n';
    }

    return 0;
}
