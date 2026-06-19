#include <iostream>
#include <cstdarg>
#include <initializer_list>
#include <variant>
#include <vector>

// Type-unsafe: Original va_arg Example
void print_va_arg(int count, ...) {
    va_list args;
    va_start(args, count);
    for (int i = 0; i < count; ++i) {
        int value = va_arg(args, int); // No type checking
        std::cout << value << " ";
    }
    va_end(args);
    std::cout << '\n';
}

// Alternative 1: Variadic Templates (Type-Safe)
template <typename... Args>
void print_variadic(Args... args) {
    (std::cout << ... << args) << '\n'; // Fold expression (C++17)
}

// Alternative 2: Using std::initializer_list
void print_initializer(std::initializer_list<int> values) {
    for (int value : values) {
        std::cout << value << " ";
    }
    std::cout << '\n';
}

// Alternative 3: Using std::variant for Heterogeneous Arguments
void print_variant(const std::vector<std::variant<int, std::string>>& values) {
    for (const auto& value : values) {
        std::visit([](const auto& v) { std::cout << v << " "; }, value);
    }
    std::cout << '\n';
}

int main() {
    std::cout << "Using va_arg (Type-Unsafe):\n";
    print_va_arg(3, 10, 20, 30); // Works
    // print_va_arg(3, 10, "string", 30); // Undefined behavior (uncomment to see issues)

    std::cout << "\nUsing Variadic Templates (Type-Safe):\n";
    print_variadic(10, 20, 30);                // Prints: 10 20 30
    print_variadic("Hello", ", ", "World!");   // Prints: Hello, World!

    std::cout << "\nUsing std::initializer_list (Homogeneous Arguments):\n";
    print_initializer({10, 20, 30});           // Prints: 10 20 30

    std::cout << "\nUsing std::variant (Heterogeneous Arguments):\n";
    print_variant({10, "hello", 20, "world"}); // Prints: 10 hello 20 world

    return 0;
}
