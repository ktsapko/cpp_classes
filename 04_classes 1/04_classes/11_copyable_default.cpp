#include <iostream>

struct Point {
	int x;
	int y;
	Point(int x_, int y_) : x{x_}, y{y_} {}
    // Incorrect to forget
    // Point() = default; // May be incomplete
    // Best one, since raw data is initialized
    Point() : Point(0, 0) {}
};

std::ostream& operator<<(std::ostream& out, const Point& p) {
    out << p.x << ":" << p.y;
    return out;
}

int main(void) {
    Point p(1, 2);
    Point p2(p);
    Point p3;
    std::cout << p2 << std::endl;
    std::cout << p3 << std::endl;
    return 0;
}