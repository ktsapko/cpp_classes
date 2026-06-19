#include <iostream>
#include <memory>

// A function that takes a reference to an object
void printData(const int& value) {
    std::cout << "Value: " << value << '\n';
}

// A function that takes a raw pointer to an object
void incrementData(int* value) {
    if (value) { // Always check if the pointer is non-null
        (*value)++;
    }
}

// Example usage
int main() {
    int data = 42;

    // Pass by reference
    printData(data);

    // Pass by raw pointer
    incrementData(&data);
    printData(data);

    // Use with smart pointers
    auto smartPtr = std::make_shared<int>(100);

    // You can use smart pointers with these functions without issue:
    printData(*smartPtr);       // Dereference and pass as a reference
    incrementData(smartPtr.get()); // Get raw pointer and pass it

    return 0;
}

/*
 * Why Prefer T* or T& in Function Arguments:
 *
 * 1. **Flexibility**:
 *    - Taking raw pointers or references allows the function to work with both stack-allocated
 *      and heap-allocated objects.
 *    - For example, `incrementData` can be called with a `std::shared_ptr`, `std::unique_ptr`,
 *      or even a plain `int` variable, making the function more reusable.
 *
 * 2. **Avoid Ownership Ambiguity**:
 *    - Passing a smart pointer (e.g., `std::shared_ptr`) suggests that the function may take
 *      ownership or extend the lifetime of the resource, which might not be the case.
 *    - Using raw pointers or references clarifies that the function does not assume ownership
 *      of the object.
 *
 * 3. **Simpler Function Contracts**:
 *    - Functions that use `T&` or `T*` focus on the object itself rather than how it's managed,
 *      reducing unnecessary coupling with specific smart pointer types.
 *
 * 4. **Efficient and Clear**:
 *    - Dereferencing a smart pointer (e.g., `*smartPtr`) is lightweight and conveys intent clearly.
 *    - `smartPtr.get()` is explicit when passing a raw pointer is necessary.
 *
 * Notes:
 * - Use `T&` for arguments that are required and non-nullable.
 * - Use `T*` for arguments that are optional (nullable).
 * - Reserve smart pointers for situations where ownership semantics are essential.
 */
