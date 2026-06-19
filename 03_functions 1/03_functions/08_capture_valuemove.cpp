#include <iostream>
#include <memory>
#include <thread>

void process(std::unique_ptr<int> value) {
    std::cout << "Processing value: " << *value << '\n';
}

int main() {
    auto local = std::make_unique<int>(123); // Create a unique_ptr

    // Wrap the lambda into a std::function that moves the unique_ptr
    std::thread t([value = std::move(local)]() mutable {
        process(std::move(value)); // Move the ownership again inside the thread
    });

    t.join(); // Wait for the thread to finish

    std::cout << "Thread completed.\n";
    std::cout << "Address: " << local.get() << std::endl;

    return 0;
}
