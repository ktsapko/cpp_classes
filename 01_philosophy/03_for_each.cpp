#include <iostream>
#include <vector>
#include <algorithm> // for std::for_each
#include <execution> // for parallel execution policies (C++17 or later)
#include <span>      // Requires C++20 for std::span

// 1. Negative Example: Exposing the index unnecessarily
void loop_exposing_index(const std::vector<int>& v) {
    for (size_t i = 0; i < v.size(); ++i) {
        std::cout << "Exposed index loop: v[" << i << "] = " << v[i] << '\n';
    }
}

// 2. Positive Example: Range-based loop (read-only)
void range_based_loop(const std::vector<int>& v) {
    for (const auto& x : v) {
        std::cout << "Range-based (read-only): " << x << '\n';
    }
}

// 3. Positive Example: Range-based loop (modifying elements)
void range_based_loop_modify(std::vector<int>& v) {
    for (auto& x : v) {
        x *= 2; // Modify the value in place
    }
}

// 4. Positive Example: Using std::for_each for intent clarity
void loop_with_for_each(const std::vector<int>& v) {
    std::for_each(v.begin(), v.end(), [](int x) {
        std::cout << "For_each: " << x << '\n';
    });
}

// 5. Positive Example: Parallel execution using std::for_each
void loop_with_parallel_for_each(const std::vector<int>& v) {
    std::for_each(std::execution::par, v.begin(), v.end(), [](int x) {
        std::cout << "Parallel for_each: " << x << '\n';
    });
}

// Main function demonstrating all examples
int main() {
    std::vector<int> numbers = {1, 2, 3, 4, 5};

    std::cout << "1. Negative Example: Exposing index unnecessarily\n";
    loop_exposing_index(numbers);

    std::cout << "\n2. Positive Example: Range-based loop (read-only)\n";
    range_based_loop(numbers);

    std::cout << "\n3. Positive Example: Range-based loop (modifying elements)\n";
    range_based_loop_modify(numbers);
    std::cout << "Modified numbers: ";
    for (const auto& x : numbers) {
        std::cout << x << ' ';
    }
    std::cout << '\n';

    std::cout << "\n4. Positive Example: Using std::for_each\n";
    loop_with_for_each(numbers);

    std::cout << "\n5. Positive Example: Parallel execution with std::for_each\n";
    loop_with_parallel_for_each(numbers);

    return 0;
}
