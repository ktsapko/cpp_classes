#include <iostream>
#include <functional>
#include <thread>
#include <vector>

void process(int value) {
    std::cout << "Processing value: " << value << '\n';
}

int main() {
    int local = 123; // Local variable

    // Capture by value to avoid dangling reference
    auto work = [local] { // Captures `local` by value
        process(local);
    };

    std::thread t(work);
    t.join(); // Safe: `local` is copied into the lambda

    std::cout << "Local variable captured by value.\n";

    return 0;
}
