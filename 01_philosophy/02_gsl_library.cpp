#include <iostream>
#include <vector>
#include <gsl/gsl> // GSL library header


/*
git clone https://github.com/microsoft/GSL.git
cd GSL
mkdir build && cd build
cmake ..
cmake --build .
sudo make install


+------------------------+-------------------------+-------------------------------+
|       Feature          |     GSL (Microsoft)    |          C++20 Equivalent     |
+------------------------+-------------------------+-------------------------------+
| gsl::span              | Provides a safer way   | std::span (fully integrated   |
|                        | to handle array-like   | into C++20; replaces gsl::span|
|                        | data without raw       | in most cases).               |
|                        | pointers.              |                               |
+------------------------+-------------------------+-------------------------------+
| gsl::string_span       | Deprecated in favor of | No direct equivalent in C++20.|
|                        | gsl::span<char> or     | Use std::span<char> for string|
|                        | std::span<char>.       | spans.                        |
+------------------------+-------------------------+-------------------------------+
| gsl::index             | Type-safe signed       | No direct equivalent in C++20.|
|                        | integer for indexing.  | Use explicit types (e.g.,     |
|                        | Helps avoid size_t vs. | std::ptrdiff_t) if needed.    |
|                        | int mismatches.        |                               |
+------------------------+-------------------------+-------------------------------+
| gsl::not_null          | Ensures a pointer is   | std::not_null is not part of  |
|                        | never null. Enforces   | C++20. Use raw pointers with  |
|                        | contracts at runtime.  | care or smart pointers.       |
+------------------------+-------------------------+-------------------------------+
| gsl::byte              | Type-safe byte         | std::byte (introduced in      |
|                        | operations (like       | C++17, unchanged in C++20).   |
|                        | std::byte).            |                               |
+------------------------+-------------------------+-------------------------------+
| gsl::narrow            | Runtime-checked type   | No direct equivalent. Use     |
|                        | conversion to avoid    | static_cast and manual checks.|
|                        | narrowing errors.      |                               |
+------------------------+-------------------------+-------------------------------+
| gsl::narrow_cast       | Explicit but unchecked | No direct equivalent. static_ |
|                        | type conversions.      | cast is used in C++20.        |
+------------------------+-------------------------+-------------------------------+
| gsl::Expects / Ensures | Lightweight contract   | Partially replaced by         |
|                        | programming for        | `std::contract` (proposed but |
|                        | preconditions and      | not yet widely available in   |
|                        | postconditions.        | compilers).                   |
+------------------------+-------------------------+-------------------------------+
| gsl::final_action      | Ensures cleanup actions| std::scope_exit from          |
|                        | are executed at scope  | `<utility>` provides similar  |
|                        | exit.                  | functionality in C++20.       |
+------------------------+-------------------------+-------------------------------+
| gsl::at                | Bounds-checked element | std::vector::at and std::span:|
|                        | access for containers. | at provide bounds checking.   |
+------------------------+-------------------------+-------------------------------+
| gsl::owner             | Annotates raw pointers | No direct equivalent. Smart   |
|                        | to indicate ownership. | pointers are preferred.       |
+------------------------+-------------------------+-------------------------------+
| gsl::finally           | Scope guard for        | std::scope_exit in C++20      |
|                        | cleanup. Similar to    | achieves the same goal.       |
|                        | gsl::final_action.     |                               |
+------------------------+-------------------------+-------------------------------+

*/


int main() {
    // Create a vector of integers
    std::vector<int> numbers = {10, 20, 30, 40, 50};

    // Use gsl::index for safe indexing
    for (gsl::index i = 0; i < gsl::narrow_cast<gsl::index>(numbers.size()); ++i) {
        std::cout << "numbers[" << i << "] = " << numbers[i] << '\n';
    }

    // gsl::index ensures explicit indexing and type safety
    gsl::index idx = 3;
    if (idx < gsl::narrow_cast<gsl::index>(numbers.size())) {
        std::cout << "Accessing numbers[" << idx << "]: " << numbers[idx] << '\n';
    } else {
        std::cerr << "Index out of bounds!\n";
    }

    return 0;
}
