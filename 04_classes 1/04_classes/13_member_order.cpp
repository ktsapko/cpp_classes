#include <iostream>

struct MyClass {
	int x;
	int y;
public:
	MyClass(int a) : y{a}, x{++a} {}
};

struct MyClass2 {
	int x;
	int y;
public:
	MyClass2(int a) : x{a}, y{++a} {}
};


int main(void) {
    MyClass m{1};
    MyClass2 m2{1};
    std::cout << m.x << ":" << m.y << std::endl;
    std::cout << m2.x << ":" << m2.y << std::endl;
}