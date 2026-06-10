#include <iostream>
#include <variant>
#include <span>
#include <exception>
#include <gsl/gsl> // For gsl::narrow_cast (Microsoft GSL)

// Helper functions
void print_array_with_pointer(int* arr, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        std::cout << arr[i] << ' ';
    }
    std::cout << '\n';
}

void print_array_with_span(std::span<int> arr) {
    for (const auto& num : arr) {
        std::cout << num << ' ';
    }
    std::cout << '\n';
}

// 1. Unions vs Variants
void process_union() {
    union Data {
        int i;
        float f;
    };

    Data d;
    d.i = 42;
    std::cout << "Accessing union as int: " << d.i << '\n';

    d.f = 3.14f; // Overwrites the previous value
    std::cout << "Accessing union as float: " << d.f << '\n';

    std::cout << "Accessing union as forced(int): " << d.i << '\n';
}

void process_variant() {
    std::variant<int, float> data;

    data = 42; // Store int
    std::cout << "Accessing variant as int: " << std::get<int>(data) << '\n';

    data = 3.14f; // Store float
    std::cout << "Accessing variant as float: " << std::get<float>(data) << '\n';

    try {
        auto value = std::get<int>(data);
        std::cout << "Accessing incorrectly variant as int: " << value << '\n';
    } catch (const std::exception& e) {
        std::cout << "Illegal access: " << e.what();
    }
}

// 2. Type Casts
void process_cast() {
    double d = 3.14;
    int i = (int)d; // C-style cast
    std::cout << "C-style cast: " << i << '\n';
}

void process_static_cast() {
    double d = 3.14;
    int i = static_cast<int>(d); // static_cast ensures explicit and type-safe conversion
    std::cout << "static_cast: " << i << '\n';
}

// 3. Array Decay to Pointer vs Span
void process_array_decay() {
    int arr[] = {1, 2, 3, 4, 5};
    print_array_with_pointer(arr, 5); // Array decays to pointer
}

void process_span() {
    int arr[] = {1, 2, 3, 4, 5};
    print_array_with_span(arr); // Use span to avoid array decay
}

// 4. Narrowing Conversions
void process_narrowing() {
    double d = 3.14;
    int i = d; // Implicit narrowing conversion
    std::cout << "Narrowing conversion: " << i << '\n';
}

void process_safe_conversion() {
    double d = 3.14;
    int i = gsl::narrow_cast<int>(d); // Ensures narrowing is explicit
    std::cout << "Explicit conversion: " << i << '\n';
}

int main() {
    std::cout << "1. Unions vs Variants:\n";
    std::cout << "Negative:\n";
    process_union();
    std::cout << "Positive:\n";
    process_variant();

    std::cout << "\n2. Type Casts:\n";
    std::cout << "Negative:\n";
    process_cast();
    std::cout << "Positive:\n";
    process_static_cast();

    std::cout << "\n3. Array Decay:\n";
    std::cout << "Negative:\n";
    process_array_decay();
    std::cout << "Positive:\n";
    process_span();

    std::cout << "\n4. Narrowing Conversions:\n";
    std::cout << "Negative:\n";
    process_narrowing();
    std::cout << "Positive:\n";
    process_safe_conversion();

    return 0;
}
