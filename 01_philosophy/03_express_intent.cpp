#include <iostream>
#include <vector>
#include <memory>
#include <span> // Requires C++20 for std::span


// 1. Negative Example: Index-based loop
void print_numbers_index_based(const std::vector<int>& numbers) {
    for (size_t i = 0; i < numbers.size(); ++i) {
        std::cout << "Index-based loop: " << numbers[i] << '\n';
    }
}

// Positive Example: Range-based loop
void print_numbers_range_based(const std::vector<int>& numbers) {
    for (const auto& num : numbers) {
        std::cout << "Range-based loop: " << num << '\n';
    }
}

// 2. Negative Example: Using raw pointers
void print_array_with_pointers(int* arr, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        std::cout << "Pointer-based: " << arr[i] << '\n';
    }
}

// Positive Example: Using std::span
void print_array_with_span(std::span<const int> arr) {
    for (const auto& num : arr) {
        std::cout << "Span-based: " << num << '\n';
    }
}

// 3. Negative Example: Loop variables in too large a scope
void loop_with_large_scope() {
    int i; // Declared outside of loop
    for (int i = 0; i < 10; ++i) {
        std::cout << "Large scope loop: " << i << '\n';
    }
    std::cout << "i after loop: " << i << " (still in scope)\n";
}

// Positive Example: Loop variables in limited scope
void loop_with_limited_scope() {
    for (int i = 0; i < 10; ++i) {
        std::cout << "Limited scope loop: " << i << '\n';
    }
    // i is out of scope here
}

// 4. Negative Example: Naked new/delete
void use_naked_new_delete() {
    int* ptr = new int(42);
    std::cout << "Naked new/delete: " << *ptr << '\n';
    delete ptr;
}

// Positive Example: Use smart pointers
void use_smart_pointers() {
    auto ptr = std::make_unique<int>(42);
    std::cout << "Smart pointer: " << *ptr << '\n';
}

// 5. Negative Example: Too many parameters of built-in types
void draw_line_with_raw_params(int x1, int y1, int x2, int y2) {
    std::cout << "Raw parameters: Drawing line from (" << x1 << ", " << y1 << ") to (" << x2 << ", " << y2 << ")\n";
}

// Positive Example: Use a struct for parameters
struct Point {
    int x, y;
};

void draw_line_with_struct(Point p1, Point p2) {
    std::cout << "Structured params: Drawing line from (" << p1.x << ", " << p1.y << ") to (" << p2.x << ", " << p2.y << ")\n";
}

// Main function demonstrating all examples
int main() {
    std::vector<int> numbers = {1, 2, 3, 4, 5};
    int arr[] = {10, 20, 30, 40, 50};

    std::cout << "1. Loops:\n";
    std::cout << "Negative Example:\n";
    print_numbers_index_based(numbers);
    std::cout << "Positive Example:\n";
    print_numbers_range_based(numbers);

    std::cout << "\n2. Arrays and Pointers:\n";
    std::cout << "Negative Example:\n";
    print_array_with_pointers(arr, 5);
    std::cout << "Positive Example:\n";
    print_array_with_span(arr);

    std::cout << "\n3. Loop Variable Scope:\n";
    std::cout << "Negative Example:\n";
    loop_with_large_scope();
    std::cout << "Positive Example:\n";
    loop_with_limited_scope();

    std::cout << "\n4. Memory Management:\n";
    std::cout << "Negative Example:\n";
    use_naked_new_delete();
    std::cout << "Positive Example:\n";
    use_smart_pointers();

    std::cout << "\n5. Function Parameters:\n";
    std::cout << "Negative Example:\n";
    draw_line_with_raw_params(0, 0, 10, 10);
    std::cout << "Positive Example:\n";
    Point p1 = {0, 0};
    Point p2 = {10, 10};
    draw_line_with_struct(p1, p2);

    return 0;
}
