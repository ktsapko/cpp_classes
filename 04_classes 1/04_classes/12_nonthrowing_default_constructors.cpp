
template <typename T>
class MyClass {
	T* items;
public:
    MyClass() : MyClass(0) {} // wasteful, possibly unsafe
    MyClass(int n) : items{new T[n]} {} // Logic here may throw
};

template <typename T>
class MyClassBetter {
	T* items;
public:
    MyClassBetter() noexcept {items = nullptr;} // Best to decouple it and offer a safe implementation
    MyClassBetter(int n) : items{new T[n]} {} 
};