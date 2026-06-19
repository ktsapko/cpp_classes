#include <iostream>
#include <memory>
#include <utility> // For std::forward

// A template function that perfectly forwards arguments to another function
template <class F, class... Args>
auto invoke(F f, Args&&... args) {
    return f(std::forward<Args>(args)...); // Forward arguments while preserving their value categories
}

// Example function to demonstrate the behavior
void process(const int& x) { // Accepts const lvalue
    std::cout << "process(const int&): " << x << '\n';
}

void process(int&& x) { // Accepts rvalue
    std::cout << "process(int&&): " << x << '\n';
}

int main() {
    int a = 42;

    // Disambiguate the overloaded process function
    auto const_process = static_cast<void(*)(const int&)>(&process);
    auto rvalue_process = static_cast<void(*)(int&&)>(&process);

    std::cout << "Calling with lvalue:\n";
    invoke(const_process, a); // Calls process(const int&)

    std::cout << "\nCalling with rvalue:\n";
    invoke(rvalue_process, 99); // Calls process(int&&)

    std::cout << "\nCalling with std::move(lvalue):\n";
    invoke(rvalue_process, std::move(a)); // Calls process(int&&)

    std::cout << "\nCalling with std::move(lvalue):\n";
    invoke(rvalue_process, std::move(a)); // Calls process(int&&)

    return 0;
}
