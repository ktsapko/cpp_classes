#include <iostream>
#include <unordered_set>
#include <functional>

// A simple class
class Point {
    int x, y;

public:
    Point(int x, int y) : x(x), y(y) {}

    // Getters
    int getX() const { return x; }
    int getY() const { return y; }

    // Equality operator
    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }

    // Nested hash struct
    struct Hash {
        std::size_t operator()(const Point& p) const noexcept {
            std::size_t h1 = std::hash<int>{}(p.getX());
            std::size_t h2 = std::hash<int>{}(p.getY());
            return h1 ^ (h2 << 1); // Combine hashes using XOR and bit-shifting
        }
    };
};

int main() {
    // Create an unordered_set with custom hash and equality
    std::unordered_set<Point, Point::Hash> points;

    // Insert points
    points.insert(Point(1, 2));
    points.insert(Point(3, 4));
    points.insert(Point(1, 2)); // Duplicate; won't be added

    // Iterate and print points
    for (const auto& p : points) {
        std::cout << "Point(" << p.getX() << ", " << p.getY() << ")\n";
    }

    return 0;
}
