#include <iostream>
#include <memory> // For std::unique_ptr

// Interface: The public class exposed to clients
class Shape {
    class impl; // Forward declaration of the implementation class
    std::unique_ptr<impl> pimpl; // Pointer to the implementation

public:
    Shape(); // Constructor
    ~Shape(); // Destructor

    void draw() const; // Public method
};

class Shape::impl { // Private implementation
public:
    void draw() const {
        std::cout << "Drawing a shape (implementation hidden)." << std::endl;
    }
};

// Definitions of Shape's methods
Shape::Shape() : pimpl(std::make_unique<impl>()) {} // Initialize pimpl
Shape::~Shape() = default; // Default destructor (pimpl automatically deleted)

void Shape::draw() const {
    pimpl->draw(); // Delegate to the implementation
}

int main() {
    Shape shape;
    shape.draw(); // Use the public interface without exposing implementation details

    return 0;
}
