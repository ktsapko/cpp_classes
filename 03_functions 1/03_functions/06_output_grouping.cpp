#include <iostream>
#include <tuple>
#include <set>
#include <string>

// Function returning a tuple
std::tuple<int, std::string> get_data() {
    return {42, "Hello, World!"}; // Return multiple values in a tuple
}

int main() {
    // Example 1: Using std::tuple and std::tie (C++11)
    int number;
    std::string message;

    std::tie(number, message) = get_data(); // Extract values from tuple
    std::cout << "Using std::tie:\n";
    std::cout << "Number: " << number << ", Message: " << message << "\n";

    // Example 2: Using structured bindings (C++17)
    std::cout << "\nUsing structured bindings:\n";
    auto [num, msg] = get_data(); // Decompose tuple into separate variables
    std::cout << "Number: " << num << ", Message: " << msg << "\n";

    // Example 3: Structured bindings with std::set's insert (C++17)
    std::set<int> my_set;
    if (auto [iter, success] = my_set.insert(99); success) {
        std::cout << "\nInserted value: " << *iter << "\n";
    } else {
        std::cout << "\nValue already exists in the set\n";
    }

    return 0;
}
