#include <iostream>
#include <thread>
#include <vector>

class Worker {
public:
    void queue_work() {
        thread_pool.emplace_back([*this] { // Captures entire object
            process(this->data);          // Uses only `data`
        });
    }

private:
    std::vector<std::thread> thread_pool;
    int data = 123;

    void process(int value) {
        std::cout << "Processing value: " << value << '\n';
    }
};


class Worker {
public:
    void queue_work() {
        int local_data = data; // Copy necessary member
        thread_pool.emplace_back([local_data] { // Captures only `local_data`
            process(local_data);
        });
    }

private:
    std::vector<std::thread> thread_pool;
    int data = 123;

    static void process(int value) {
        std::cout << "Processing value: " << value << '\n';
    }
};
