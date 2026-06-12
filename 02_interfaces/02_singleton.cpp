#include <iostream>

class Singleton {
public:
    // Get the single instance of the class
    static Singleton& getInstance() {
        static Singleton instance; // Guaranteed to be created only once
        return instance;
    }

    // Example method
    void doSomething() {
        std::cout << "Singleton instance address: " << this << "\n";
    }

private:
    // Private constructor to prevent instantiation
    Singleton() {
        std::cout << "Singleton created\n";
    }

    // Delete copy constructor and assignment operator to prevent copies
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
};

int main() {
    Singleton& s1 = Singleton::getInstance();
    s1.doSomething();

    Singleton& s2 = Singleton::getInstance();
    s2.doSomething();

    std::cout << "Address s1: " << &s1 << std::endl;
    std::cout << "Address s2: " << &s2 << std::endl;

    // Both calls to getInstance() return the same instance
    return 0;
}
