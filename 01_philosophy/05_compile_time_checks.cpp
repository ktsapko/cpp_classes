#include <iostream>
#include <span>
#include <cstdint> // For int32_t

// Negative Example: Avoidable runtime checks for type size
void check_int_size() {
    int bits = 0;
    for (int i = 1; i; i <<= 1) { // Undefined behavior on overflow
        ++bits;
    }

    if (bits < 32) {
        std::cerr << "Int too small\n"; // Run-time error
    }
}

// Positive Example: Compile-time check with static_assert
void check_static_assert() {
    static_assert(sizeof(int) >= 4, "Int is too small for this application");
    std::cout << "Static assertion passed: int is large enough\n";
}

// Better Example: Use int32_t for guaranteed 32-bit integers
void check_with_int32_t() {
    static_assert(sizeof(int32_t) == 4, "int32_t should always be 4 bytes");
    int32_t myInt = 0; // Guaranteed to be a 32-bit integer
    std::cout << "Using int32_t for type safety: " << myInt << '\n';
}

// Negative Example: Pointer arguments prone to errors
void read_with_pointer(int* p, int n) {
    for (int i = 0; i < n; ++i) {
        p[i] = i; // Simulating reading
    }
}

// Positive Example: Use std::span for range safety
void read_with_span(std::span<int> r) {
    for (size_t i = 0; i < r.size(); ++i) {
        r[i] = static_cast<int>(i); // Simulating reading
    }
}

int main() {
    std::cout << "1. Checking integer type size:\n";
    std::cout << "Negative Example:\n";
    check_int_size();
    std::cout << "Positive Example:\n";
    check_static_assert();
    check_with_int32_t();

    std::cout << "\n2. Safer function arguments:\n";

    // Negative Example
    std::cout << "Negative Example:\n";
    int a[100];
    read_with_pointer(a, 1000); // Unsafe: Goes over the end of the array

    // Positive Example
    std::cout << "Positive Example:\n";
    int b[100];
    read_with_span(b); // Safe: Compiler deduces size

    std::cout << "Array content after read_with_span: ";
    for (const auto& val : b) {
        std::cout << val << ' ';
    }
    std::cout << '\n';

    return 0;
}
