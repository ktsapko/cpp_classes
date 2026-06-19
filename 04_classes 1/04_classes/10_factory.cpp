#include <iostream>
#include <string>

// Bad Example: Incomplete Initialization
class MyClassIncomplete {
private:
    std::string name;
    int value;

public:
    MyClassIncomplete() : value(0) {} // Constructor leaves `name` uninitialized

    void init(const std::string& name, int value) {
        this->name = name;
        this->value = value;
    }

    void display() const {
        if (name.empty()) {
            std::cout << "Error: Object not initialized properly!" << std::endl;
            return;
        }
        std::cout << "Name: " << name << ", Value: " << value << std::endl;
    }
};

// Good Example: Using Factory Function with Controlled Initialization
class MyClassFactory {
public:
    // Factory function ensures the object is fully initialized
    static MyClassIncomplete create(const std::string& name, int value) {
        if (name.empty()) {
            throw std::invalid_argument("Name cannot be empty!");
        }
        if (value <= 0) {
            throw std::invalid_argument("Value must be positive!");
        }
        MyClassIncomplete obj;
        obj.init(name, value);
        return obj;
    }
};

int main() {
    std::cout << "Bad Example:" << std::endl;
    MyClassIncomplete obj1;
    obj1.display(); // Error: Object not initialized properly!

    obj1.init("Example", 42);
    obj1.display();

    std::cout << "Good Example with Factory Function:" << std::endl;
    try {
        MyClassIncomplete obj2 = MyClassFactory::create("FactoryObject", 100);
        obj2.display();

        // Uncomment this to test invalid arguments
        // MyClassFactory obj3 = MyClassFactory::create("", -1); // Throws exception
    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
    }

    return 0;
}
