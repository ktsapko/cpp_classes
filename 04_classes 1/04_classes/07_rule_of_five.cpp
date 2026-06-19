#include <iostream>
#include <vector>
#include <string>

// Rule of Five: Custom resource management
class RuleOfFive {
private:
    std::string name;
    std::vector<int> data;

public:
    // Default Constructor
    RuleOfFive(const std::string& name = "Default") : name(name) {
        std::cout << "Default Constructor called for: " << name << "\n";
    }

    // Destructor
    ~RuleOfFive() {
        std::cout << "Destructor called for: " << name << "\n";
    }

    // Copy Constructor
    RuleOfFive(const RuleOfFive& other) : name(other.name), data(other.data) {
        std::cout << "Copy Constructor called for: " << name << "\n";
    }

    // Copy Assignment Operator
    RuleOfFive& operator=(const RuleOfFive& other) {
        if (this != &other) {
            name = other.name;
            data = other.data;
            std::cout << "Copy Assignment called for: " << name << "\n";
        }
        return *this;
    }

    // Move Constructor
    RuleOfFive(RuleOfFive&& other) noexcept : name(std::move(other.name)), data(std::move(other.data)) {
        std::cout << "Move Constructor called for: " << name << "\n";
    }

    // Move Assignment Operator
    RuleOfFive& operator=(RuleOfFive&& other) noexcept {
        if (this != &other) {
            name = std::move(other.name);
            data = std::move(other.data);
            std::cout << "Move Assignment called for: " << name << "\n";
        }
        return *this;
    }

    void addData(int value) {
        data.push_back(value);
    }

    void printData() const {
        std::cout << "Data for " << name << ": ";
        for (int val : data) {
            std::cout << val << " ";
        }
        std::cout << "\n";
    }
};

// Rule of Zero: Let STL manage everything
class RuleOfZero {
private:
    std::string name;
    std::vector<int> data;

public:
    RuleOfZero(const std::string& name = "Default") : name(name) {}

    void addData(int value) {
        data.push_back(value);
    }

    void printData() const {
        std::cout << "Data for " << name << ": ";
        for (int val : data) {
            std::cout << val << " ";
        }
        std::cout << "\n";
    }
};

int main() {
    std::cout << "Rule of Five Example:\n";
    RuleOfFive obj1("Object1");
    obj1.addData(10);
    obj1.addData(20);
    obj1.printData();

    RuleOfFive obj2 = obj1; // Copy Constructor
    obj2.printData();

    RuleOfFive obj3 = std::move(obj1); // Move Constructor
    obj3.printData();

    RuleOfFive obj4("Object4");
    obj4 = obj2; // Copy Assignment
    obj4.printData();

    obj4 = std::move(obj3); // Move Assignment
    obj4.printData();

    std::cout << "\nRule of Zero Example:\n";
    RuleOfZero zero1("Zero1");
    zero1.addData(30);
    zero1.addData(40);
    zero1.printData();

    RuleOfZero zero2 = zero1; // Default copy and move provided by STL types
    zero2.printData();

    RuleOfZero zero3 = std::move(zero1); // Default move
    zero3.printData();

    return 0;
}
