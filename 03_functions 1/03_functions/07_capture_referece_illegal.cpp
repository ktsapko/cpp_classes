#include <iostream>
#include <functional>
#include <thread>
#include <vector>

void process(int value) {
    std::cout << "Processing value: " << value << '\n';
}

int main() {
    int local = 123; // Local variable

    // Simulating a thread pool with a lambda capturing by reference
    auto work = [&] {
        process(local); // Dangerous: Captures by reference
    };

    std::thread t(work);
    t.join(); // Ensures this example won't crash, but in real code, it's dangerous!
    // What happens if we get out of this function while the other thread is still running?

    std::cout << "Local variable captured by reference.\n";

    return 0;
}
