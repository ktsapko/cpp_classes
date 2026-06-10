#include <vector>
#include <string>
#include <algorithm>
#include <iostream>

// Purpose of variable in type

class Month {
    public:
    Month(int value) {
        if (value > 12)
            value = 12;
        if (value < 1)
            value = 1;
        value = value;
    };
    private:
    int value;
};


class Date {
public:
    Month month() const;  // do
    int month();          // don't
    // ...
};






// Usage of std lib functions instead of reinventing the wheel


void f(std::vector<std::string>& v)
{
    std::string val;
    std::cin >> val;
    // ...
    int index = -1;                    // bad, plus should use gsl::index
    for (int i = 0; i < v.size(); ++i) {
        if (v[i] == val) {
            index = i;
            break;
        }
    }
    // ...
}

void f2(std::vector<std::string>& v)
{
    std::string val;
    std::cin >> val;
    // ...
    auto p = std::find(v.begin(), v.end(), val);  // better
    // ...
}



// Adding units and significance to the values we are using


// bad: what does m signify?
void change_distance(double m) {
    // ...;
    // Does this say anything?
    change_distance(2.3);
}


class Meters {
public:
    explicit Meters(double value) : value_(value) {}

    double value() const { return value_; }

    friend std::ostream& operator<<(std::ostream& os, const Meters& meters) {
        os << meters.value_ << " meters";
        return os;
    }

private:
    double value_;
};

// User-defined literal
Meters operator"" _m(long double value) {
    return Meters(static_cast<double>(value));
}

Meters operator"" _mm(long double value) {
    return Meters(static_cast<double>(value) * 1e-3);
}

// better: the meaning of s is specified
void change_distance(Meters m) {
    // error: no unit
    // (here we get not error because we have the double one defined)
    change_distance(2.3);

    // we move 2.3 meters
    change_distance(2.3_m);
    
    // we move 2.3 milimeters
    change_distance(2.3_mm);
}

int main(void) {
    return 0;
}

