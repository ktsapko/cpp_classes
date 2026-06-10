#include <iostream>
#include <vector>
#include <cstdlib> // for malloc and realloc

int main() {
    // Low-level, verbose, and error-prone example:
    int sz = 100;
    int* p = (int*) malloc(sizeof(int) * sz);
    int count = 0;
    // ...
    for (;;) {
        // ... read an int into x, exit loop if end of file is reached ...
        // ... check that x is valid ...
        if (count == sz)
            p = (int*) realloc(p, sizeof(int) * sz * 2);
        p[count++] = x;
        // ...
    }

    /*
     * This is low-level, verbose, and error-prone.
     * For example, we “forgot” to test for memory exhaustion.
     */

    // Improved example using vector:
    std::vector<int> v;
    v.reserve(100);
    // ...
    for (int x; std::cin >> x; ) {
        // ... check that x is valid ...
        v.push_back(x);
    }

    /*
     * Note:
     * The standard library and the GSL are examples of this philosophy.
     * For example, instead of messing with the arrays, unions, casts, tricky lifetime issues,
     * gsl::owner, etc., that are needed to implement key abstractions, such as vector, span,
     * lock_guard, and future, we use the libraries designed and implemented by people with more 
     * time and expertise than we usually have.
     *
     * Similarly, we can and should design and implement more specialized libraries, rather than
     * leaving the users (often ourselves) with the challenge of repeatedly getting low-level
     * code well.
     *
     * This is a variant of the subset of superset principle that underlies these guidelines.
     */
}
