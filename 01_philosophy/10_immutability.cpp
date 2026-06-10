#include <iostream>
#include <vector>
#include <string>

class Person {
private:
    const std::string name; // Immutable field
    const int age;          // Immutable field

public:
    Person(const std::string& name, int age) : name(name), age(age) {}

    // Accessor methods
    const std::string& getName() const { return name; }
    int getAge() const { return age; }

    // No mutators (no setters) to ensure immutability
};

int main() {
    // Immutable object
    // Protection is ensured even without const.
    const Person person("Alice", 30);

    std::cout << "Name: " << person.getName() << "\n";
    std::cout << "Age: " << person.getAge() << "\n";

    // Attempting to modify 'person' or its fields will result in a compile-time error.
    // Example:
    // person.age = 31;      // Error: cannot assign to a const member
    // person.name = "Bob";  // Error: cannot assign to a const member

    return 0;
}
