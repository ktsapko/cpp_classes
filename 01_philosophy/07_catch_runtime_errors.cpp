#include <iostream>
#include <vector>
#include <string>
#include <cmath> // for sqrt
#include <span>  // for std::span (requires C++20)

// Example 1: Error-prone pointer and count interface
void increment1(int* p, int n) // Bad: prone to out-of-range errors
{
    for (int i = 0; i < n; ++i) {
        ++p[i];
    }
}

void use1(int m) {
    const int n = 10;
    int a[n] = {};
    increment1(a, m); // Risky: m may exceed the size of 'a'
}


//Here we made a small error in use1 that will lead to corrupted data or a crash.
// The (pointer, count)-style interface leaves increment1() with no realistic way of defending itself against out-of-range errors.
// If we could check subscripts for out of range access, then the error would not be discovered until p[10] was accessed.
// We could check earlier and improve the code:


// Improved: Using std::span for safer range checking
void increment2(std::span<int> p) {
    for (int& x : p) {
        ++x;
    }
}

void use2(int m) {
    const int n = 10;
    int a[n] = {};
    increment2({a, m}); // maybe typo, maybe m <= n is supposed
}

// Now, m <= n can be checked at the point of call (early) rather than later.
// If all we had was a typo so that we meant to use n as the bound,
// the code could be further simplified (eliminating the possibility of an error):

void use3() {
    const int n = 10;
    int a[n] = {};
    increment2(a); // Compiler deduces size of 'a', eliminating errors
}


// Don’t repeatedly check the same value. Don’t pass structured data as strings:


// Example 2: Structured data validation and excessive checking
class Date {
public:
    // Assume validation
    Date(int day, int month, int year) : day(day), month(month), year(year) {}

    static Date read_date(std::istream& is) {
        int day, month, year;
        is >> day >> month >> year;
        return Date(day, month, year);
    }

    static Date extract_date(const std::string& s) {
        int day, month, year;
        sscanf(s.c_str(), "%d/%d/%d", &day, &month, &year);
        return Date(day, month, year);
    }

    std::string to_string() const {
        return std::to_string(day) + "/" + std::to_string(month) + "/" + std::to_string(year);
    }

private:
    int day;
    int month;
    int year;
};

void user1(const std::string& date) {
    Date d = Date::extract_date(date); // Validate string
    // Do something with d
}

void user2() {
    // The date is validated twice (by the Date constructor) and passed as a character string (unstructured data).
    Date d = Date::read_date(std::cin); // Read directly from stream
    user1(d.to_string());               // Pass date as string (redundant validation)
}


// Excess checking can be costly.
// There are cases where checking early is inefficient because you might never need the value, 
// or might only need part of the value that is more easily checked than the whole.
// Similarly, don’t add validity checks that change the asymptotic behavior of your interface
// (e.g., don’t add a O(n) check to an interface with an average complexity of O(1)).


// Example 3: Avoiding excessive validation
class Jet {
    float x;
    float y;
    float z;
    float e;

public:
    // Should I check here that the values are physically meaningful?
    Jet(float x, float y, float z, float e) : x(x), y(y), z(z), e(e) {}

    float m() const {
        // Should I handle the degenerate case here?
        return std::sqrt(x * x + y * y + z * z - e * e);
    }

    bool is_physically_valid() const {
        // Check if the values satisfy the physical law: e * e < x * x + y * y + z * z
        // The physical law for a jet (e * e < x * x + y * y + z * z) is not an invariant because of the possibility for measurement errors.
        return (e * e < (x * x + y * y + z * z));
    }
};

void process_jet() {
    Jet jet(1.0, 2.0, 3.0, 2.5);
    if (jet.is_physically_valid()) {
        std::cout << "Jet is physically valid. Mass: " << jet.m() << "\n";
    } else {
        std::cout << "Jet is not physically valid.\n";
    }
}

// Main function to demonstrate all cases
int main() {
    // Demonstrate error-prone and improved interfaces
    std::cout << "1. Increment examples:\n";
    std::cout << "Using increment1 (error-prone):\n";
    use1(6); // Risky example

    std::cout << "\nUsing increment2 (span-based):\n";
    use2(5);

    std::cout << "\nUsing increment2 with inferred size:\n";
    use3();

    // Demonstrate structured data validation
    std::cout << "\n2. Date validation examples:\n";
    std::cout << "Enter a date (day month year): ";
    user2();

    // Demonstrate Jet physical law validation
    std::cout << "\n3. Jet validation example:\n";
    process_jet();

    return 0;
}
