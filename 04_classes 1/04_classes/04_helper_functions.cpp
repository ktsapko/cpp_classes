#include <iostream>
#include <cmath>

namespace Geometry {

class Point {
private:
    double x, y;

public:
    Point(double x = 0.0, double y = 0.0) : x(x), y(y) {}

    double getX() const { return x; }
    double getY() const { return y; }

    void setX(double newX) { x = newX; }
    void setY(double newY) { y = newY; }

    void print() const {
        std::cout << "(" << x << ", " << y << ")\n";
    }
};

// Helper functions in the same namespace as Point
double distance(const Point& p1, const Point& p2) {
    double dx = p2.getX() - p1.getX();
    double dy = p2.getY() - p1.getY();
    return std::sqrt(dx * dx + dy * dy);
}

Point midpoint(const Point& p1, const Point& p2) {
    double mx = (p1.getX() + p2.getX()) / 2.0;
    double my = (p1.getY() + p2.getY()) / 2.0;
    return Point(mx, my);
}

} // namespace Geometry

int main() {
    Geometry::Point p1(1.0, 2.0);
    Geometry::Point p2(4.0, 6.0);

    p1.print();
    p2.print();

    std::cout << "Distance: " << Geometry::distance(p1, p2) << "\n";
    Geometry::Point mid = Geometry::midpoint(p1, p2);
    std::cout << "Midpoint: ";
    mid.print();

    return 0;
}
