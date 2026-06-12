// Helper functions to represent preconditions and postconditions
// In case we don't want GSL.
// #define Expects(condition) assert(condition) // For preconditions
// #define Ensures(condition) assert(condition) // For postconditions


#include <iostream>
#include <cmath>    // For std::sqrt
#include <gsl/gsl>  // For Expects and Ensures

// Example: Square root function with GSL's preconditions and postconditions
double sqrt_with(double x) {
    Expects(x >= 0); // Precondition: x must be non-negative

    double result = std::sqrt(x);

    Ensures(result >= 0); // Postcondition: result must be non-negative
    return result;
}

// RAII example: Managing a resource with GSL guarantees
// This system is used for mutexes for example
class Resource {
public:
    explicit Resource(const std::string& name) : name(name), acquired(true) {
        std::cout << "Resource '" << name << "' acquired.\n";
    }

    ~Resource() {
        if (acquired) {
            std::cout << "Resource '" << name << "' released.\n";
        }
    }

    void release() {
        if (acquired) {
            std::cout << "Resource '" << name << "' explicitly released.\n";
            acquired = false;
        }
    }

private:
    std::string name;
    bool acquired;
};

double sqrt_with_RAII(double x) {
    Expects(x >= 0); // Precondition: x must be non-negative

    // Acquire a resource
    Resource tempResource("Temporary Calculation");

    double result = std::sqrt(x);

    // Resource will be released when `tempResource` goes out of scope (RAII).
    Ensures(result >= 0); // Postcondition: result must be non-negative

    return result;
}

int main() {
    try {
        // Using preconditions and postconditions with GSL
        double result = sqrt_with(25.0);
        std::cout << "sqrt(25.0) = " << result << "\n";

        // Demonstrating RAII with GSL
        result = sqrt_with_RAII(16.0);
        std::cout << "sqrt(16.0) = " << result << "\n";

        // Uncommenting the following line will trigger the precondition failure:
        // double invalidResult = sqrt_with(-4.0);
    } catch (const std::exception& e) {
        std::cerr << "Exception caught: " << e.what() << "\n";
    }

    return 0;
}

/*
 * Explanation:
 *
 * 1. GSL `Expects`:
 *    - Ensures that a function’s input meets the required conditions before proceeding.
 *    - Example: `Expects(x >= 0);` ensures that the input to `sqrt_with` is valid.
 *
 * 2. GSL `Ensures`:
 *    - Guarantees that a function’s output satisfies the required conditions.
 *    - Example: `Ensures(result >= 0);` ensures that the result of the square root is valid.
 *
 * 3. RAII and GSL:
 *    - RAII (Resource Acquisition Is Initialization) ensures resources are properly managed.
 *    - Using `Expects` and `Ensures` with RAII adds stronger guarantees for correctness.
 *    - In the `sqrt_with_RAII` example, the `Resource` object is automatically released
 *      when it goes out of scope, ensuring proper cleanup.
 */