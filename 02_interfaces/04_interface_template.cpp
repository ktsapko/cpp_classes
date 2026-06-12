#include <iostream>
#include <concepts> // For standard concepts like std::integral and std::floating_point
#include <type_traits>

// A simple add function that requires both parameters to be arithmetic types
template<typename T, typename U>
requires std::is_arithmetic_v<T> && std::is_arithmetic_v<U>
auto add(T a, U b) {
    return a + b;
}

int main() {
    std::cout << "Adding integers: " << add(5, 10) << '\n';          // OK: Both are integers
    std::cout << "Adding double and int: " << add(5.5, 10) << '\n'; // OK: double and int are arithmetic types

    // Uncommenting the following line will result in a compile-time error:
    // std::cout << "Adding string and int: " << add(std::string("hello"), 10) << '\n';

    return 0;
}
