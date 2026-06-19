#include <iostream>
#include <memory>
#include <utility> // For std::forward

// A template function that perfectly forwards arguments to another function
template <class F, class... Args>
auto invoke(F f, Args&&... args) {
    return f(std::forward<Args>(args)...); // Forward arguments while preserving their value categories
}

// Example functions to demonstrate the behavior
void process(const std::unique_ptr<int>& ptr) { // Accepts const lvalue reference to unique_ptr
    std::cout << "process(const std::unique_ptr<int>&): " << *ptr << '\n';
}

void process(std::unique_ptr<int>&& ptr) { // Accepts rvalue unique_ptr
    if (ptr) {
        std::unique_ptr<int> x{std::move(ptr)};
        std::cout << "process(std::unique_ptr<int>&&): " << *x << '\n';
    }
    else 
        std::cout << "process(nullptr)" << "\n";
}

int main() {
    auto lvalue_ptr = std::make_unique<int>(42); // Create a unique_ptr

    // Disambiguate the overloaded process function
    auto const_process = static_cast<void(*)(const std::unique_ptr<int>&)>(&process);
    auto rvalue_process = static_cast<void(*)(std::unique_ptr<int>&&)>(&process);

    std::cout << "Calling with lvalue unique_ptr:\n";
    invoke(const_process, lvalue_ptr); // Calls process(const std::unique_ptr<int>&)

    std::cout << "\nCalling with rvalue unique_ptr:\n";
    invoke(rvalue_process, std::make_unique<int>(99)); // Calls process(std::unique_ptr<int>&&)

    std::cout << "\nCalling with std::move(lvalue unique_ptr):\n";
    invoke(rvalue_process, std::move(lvalue_ptr)); // Calls process(std::unique_ptr<int>&&)

    std::cout << "\nCalling with std::move(lvalue unique_ptr):\n";
    invoke(rvalue_process, std::move(lvalue_ptr)); // Calls process(std::unique_ptr<int>&&)

    return 0;
}
