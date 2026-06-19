#include <iostream>
#include <string>

enum class Color { Red, Green, Blue, None };

class GraphicObject {
private:
    double scale_factor = 1.0;
    double rotation_angle = 0.0;
    Color color = Color::None;

public:
    // Scale the object
    GraphicObject& scale(double factor) {
        scale_factor *= factor;
        std::cout << "Scaled by " << factor << ", new scale factor: " << scale_factor << "\n";
        return *this; // Return the current object to enable chaining
    }

    // Rotate the object
    GraphicObject& rotate(double angle) {
        rotation_angle += angle;
        std::cout << "Rotated by " << angle << " degrees, new rotation angle: " << rotation_angle << "\n";
        return *this; // Return the current object to enable chaining
    }

    // Set the object's color
    GraphicObject& setColor(Color c) {
        color = c;
        std::string color_name = (c == Color::Red) ? "Red" :
                                 (c == Color::Green) ? "Green" :
                                 (c == Color::Blue) ? "Blue" : "None";
        std::cout << "Color set to " << color_name << "\n";
        return *this; // Return the current object to enable chaining
    }
};

int main() {
    GraphicObject obj;

    // Chaining methods
    obj.scale(2.0).rotate(90).setColor(Color::Red);

    return 0;
}
