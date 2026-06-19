#include <iostream>
#include <memory>

// Interface: Defines the behavior of a shape
class Shape {
public:
    virtual ~Shape() = default; // Virtual destructor
    virtual void draw() const = 0; // Pure virtual function
    virtual double area() const = 0; // Pure virtual function
};

// Implementation: Circle
class Circle : public Shape {
private:
    double radius;

public:
    explicit Circle(double r) : radius(r) {}

    void draw() const override {
        std::cout << "Drawing a Circle with radius: " << radius << '\n';
    }

    double area() const override {
        return 3.14159 * radius * radius;
    }
};

// Implementation: Rectangle
class Rectangle : public Shape {
private:
    double width, height;

public:
    Rectangle(double w, double h) : width(w), height(h) {}

    void draw() const override {
        std::cout << "Drawing a Rectangle with width: " << width
                  << " and height: " << height << '\n';
    }

    double area() const override {
        return width * height;
    }
};

int main() {
    // Interface pointers to concrete implementations
    std::unique_ptr<Shape> circle = std::make_unique<Circle>(5.0);
    std::unique_ptr<Shape> rectangle = std::make_unique<Rectangle>(4.0, 6.0);

    // Use the interface to interact with the implementations
    circle->draw();
    std::cout << "Circle area: " << circle->area() << "\n\n";

    rectangle->draw();
    std::cout << "Rectangle area: " << rectangle->area() << '\n';

    return 0;
}
