
#include <memory>

// A non-virtual public destructor leads to undefined behavior at the moment of derived class destruction.
// If a destructor is protected, a caller cannot destroy an object that throw a base class pointer, so the destructor does not need to be virtual.

struct Base { // public non-virtual destructor is generated implicitly
	virtual void f();
};

struct Derived : Base {
	~Derived() { }
};

int main(void)
{
    std::unique_ptr<Base> p  = std::make_unique<Derived>();
} // p calls Base destructor


// Use:
// public & virtual
// protected & non-virtual