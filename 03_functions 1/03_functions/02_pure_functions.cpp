#include <iostream>
#include <ctime>

// Pure function: Computes the square of a number
double square(double x) {
    return x * x; // No side effects, depends only on input
}

// Impure function: Computes the square of a number and modifies a global variable
double result = 0.1; // Global state

double square_impure(double x) {
    result = x * x; // Modifies global state (side effect)
    return result;
}

double random_0_to_1() {
    std::time_t current_time = std::time(nullptr); // Get the current time in seconds
    return static_cast<double>(current_time % 1000) / 1000.0; // Scale to [0, 1]
}

double square_impure2(double x) {
    result = random_0_to_1(); // Modifies global state (side effect)
    // Unstable output
    return x * x  + result;
}

int main() {
    double value = 5.0;

    // Using the pure function
    std::cout << "Using pure function:\n";
    double pure_result = square(value);
    std::cout << "Square of " << value << " is " << pure_result << '\n';
    std::cout << "Global result variable modified to: " << result << '\n';

    // Using the impure function
    std::cout << "\nUsing impure function:\n";
    double impure_result = square_impure(value);

    std::cout << "Square of " << value << " is " << impure_result << '\n';
    std::cout << "Global result variable modified to: " << result << '\n';

    // Using the impure function
    std::cout << "\nUsing impure function:\n";
    double impure_result2 = square_impure2(value);

    std::cout << "Square of " << value << " is " << impure_result2 << '\n';
    std::cout << "Global result variable modified to: " << result << '\n';

    return 0;
}
