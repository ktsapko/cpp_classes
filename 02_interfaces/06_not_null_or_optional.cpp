#include <iostream>
#include <optional> // For std::optional
#include <cstring>  // For std::strlen
#include <gsl/gsl>  // For gsl::not_null

// Function that requires a non-null pointer
int length(gsl::not_null<const char*> p) {
    // No need to check for nullptr; guaranteed by gsl::not_null
    return std::strlen(p);
}

// Function that allows a nullable pointer
std::optional<int> nullable_length(const char* p) {
    if (p == nullptr) {
        return std::nullopt; // Indicate absence of value
    }
    return std::strlen(p); // Return the length if valid
}

// Function combining gsl::not_null and std::optional
std::optional<int> process_string(const gsl::not_null<const char*> p) {
    // Process the string in a way that always guarantees non-null input
    int length_result = std::strlen(p);
    if (length_result > 5) {
        return length_result; // Return the length as a valid optional value
    }
    return std::nullopt; // Return no value for strings shorter than 5
}

int main() {
    const char* str = "Hello, world!";
    const char* null_str = nullptr;

    // 1. Using length() with not_null
    try {
        std::cout << "Non-nullable length of str: " << length(str) << "\n";

        // Uncommenting the following line will throw an exception:
        // std::cout << "Non-nullable length of null_str: " << length(null_str) << "\n";

    } catch (const std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << "\n";
    }

    // 2. Using nullable_length() with nullable pointers
    std::optional<int> result1 = nullable_length(str);
    if (result1) {
        std::cout << "Nullable length of str: " << *result1 << "\n";
    } else {
        std::cout << "Nullable length of str: nullopt (nullptr input)\n";
    }

    std::optional<int> result2 = nullable_length(null_str);
    if (result2) {
        std::cout << "Nullable length of null_str: " << *result2 << "\n";
    } else {
        std::cout << "Nullable length of null_str: nullopt (nullptr input)\n";
    }

    // 3. Using process_string() combining gsl::not_null and std::optional
    try {
        std::optional<int> processed_result = process_string(str);
        if (processed_result) {
            std::cout << "Processed result (valid): " << *processed_result << "\n";
        } else {
            std::cout << "Processed result: nullopt (string too short)\n";
        }

        // Uncommenting the following line will throw an exception:
        // std::optional<int> invalid_result = process_string(null_str);

    } catch (const std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << "\n";
    }

    return 0;
}

/*
 * Explanation:
 *
 * 1. Non-Nullable Function (`length`):
 *    - Uses `gsl::not_null` to guarantee that the input pointer is not null.
 *    - Passing a `nullptr` results in a runtime exception.
 *
 * 2. Nullable Function (`nullable_length`):
 *    - Accepts raw pointers and returns a `std::optional` to indicate a valid or null result.
 *    - If the input is null, it returns `std::nullopt`.
 *
 * 3. Combined Function (`process_string`):
 *    - Combines `gsl::not_null` for stricter input validation with `std::optional` to indicate whether
 *      processing succeeded or failed.
 *    - Demonstrates how both approaches can be used together for clear input/output semantics.
 *
 * Notes:
 * - This approach ensures compile-time clarity (non-nullable) and runtime safety (nullable).
 * - Combining `std::optional` and `gsl::not_null` creates robust APIs that are self-documenting and safer.
 */
