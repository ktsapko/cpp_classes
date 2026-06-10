#include <memory>
#include <vector>
#include <span>
#include <gsl/gsl>

// Example, bad
// separately compiled, possibly dynamically loaded
extern void f(int* p);

void g(int n) {
    // bad: the number of elements is not passed to f()
    f(new int[n]);
}

// Here, a crucial bit of information (the number of elements) has been so thoroughly “obscured” that static analysis is probably rendered infeasible and dynamic checking can be very difficult when f() is part of an ABI so that we cannot “instrument” that pointer. We could embed helpful information into the free store, but that requires global changes to a system and maybe to the compiler. What we have here is a design that makes error detection very hard.
// Example, bad We can of course pass the number of elements along with the pointer:

// separately compiled, possibly dynamically loaded
extern void f2(int* p, int n);

void g2(int n) {
    f2(new int[n], m);  // bad: a wrong number of elements can be passed to f()
}

// Passing the number of elements as an argument is better (and far more common) than just passing the pointer and relying on some (unstated) convention for knowing or discovering the number of elements. However (as shown), a simple typo can introduce a serious error. The connection between the two arguments of f2() is conventional, rather than explicit.
// Also, it is implicit that f2() is supposed to delete its argument (or did the caller make a second mistake?).
// Example, bad The standard library resource management pointers fail to pass the size when they point to an object:

// separately compiled, possibly dynamically loaded
// NB: this assumes the calling code is ABI-compatible, using a
// compatible C++ compiler and the same stdlib implementation
extern void f3(std::unique_ptr<int[]>, int n);

void g3(int n) {
    f3(std::make_unique<int[]>(n), m);    // bad: pass ownership and size separately
}

// Example We need to pass the pointer and the number of elements as an integral object:
extern void f4(std::vector<int>&);   // separately compiled, possibly dynamically loaded
extern void f4(std::span<int>);      // separately compiled, possibly dynamically loaded
                                // NB: this assumes the calling code is ABI-compatible, using a
                                // compatible C++ compiler and the same stdlib implementation

void g3(int n) {
    std::vector<int> v(n);
    f4(v);                          // pass a reference, retain ownership
    f4(std::span<int>{v});          // pass a view, retain ownership
}

// This design carries the number of elements along as an integral part of an object, so that errors are unlikely and dynamic (run-time) checking is always feasible, if not always affordable.
// Example: How do we transfer both ownership and all information needed for validating use?

std::vector<int> f5(int n)          // OK: move
{
    std::vector<int> v(n);
    // ... initialize v ...
    return v;
}

std::unique_ptr<int[]> f6(int n)    // bad: loses n
{
    auto p = std::make_unique<int[]>(n);
    // ... initialize *p ...
    return p;
}

gsl::owner<int*> f7(int n)          // bad: loses n and we might forget to delete
{
    gsl::owner<int*> p = new int[n];
    // ... initialize *p ...
    return p;
}

