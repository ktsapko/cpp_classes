#include <iostream>
#include <chrono>

// Pass-by-reference
void byReference(const int& x) {
    int y = x; // Access through reference (may involve dereferencing internally)
}

// Pass-by-value
void byValue(int x) {
    int y = x; // Direct access to value (no indirection)
}

int main() {
    int value = 42;

    const int iterations = 100000000;

    // Measure pass-by-reference
    auto start1 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < iterations; ++i) {
        byReference(value);
    }
    auto end1 = std::chrono::high_resolution_clock::now();

    // Measure pass-by-value
    auto start2 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < iterations; ++i) {
        byValue(value);
    }
    auto end2 = std::chrono::high_resolution_clock::now();

    std::cout << "Pass-by-reference time: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end1 - start1).count()
              << " ms\n";

    std::cout << "Pass-by-value time: "
              << std::chrono::duration_cast<std::chrono::milliseconds>(end2 - start2).count()
              << " ms\n";

    return 0;
}
