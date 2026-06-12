#include <iostream>
#include <cerrno> // For errno

// Example demonstrating issues with global state and error reporting

// Problematic function: Relies on a global flag, making its behavior unpredictable
bool flag = true; // Global variable

double f(double d) {
    return (flag) ? d : 2 * d; // Using a global flag is unobvious. The same input may produce different results.
}

// Problematic function: Reports errors via a global variable (errno)
void f(int x) {
    if (x < 0) {
        errno = EINVAL; // Reporting through a non-local variable can be easily ignored.
        return;
    }
    // ... other processing ...
}

int main() {
    // Demonstrate the issues
    double input = 5.0;

    // Issue 1: Unpredictable results due to reliance on a global flag
    std::cout << "Flag is true: f(5.0) = " << f(input) << '\n';
    flag = false; // Change the global state
    std::cout << "Flag is false: f(5.0) = " << f(input) << '\n';

    // Issue 2: Ignoring errors reported through errno
    f(-1); // Invalid input
    if (errno == EINVAL) {
        std::cerr << "Error: Invalid input for f(int).\n";
    }

    return 0;
}