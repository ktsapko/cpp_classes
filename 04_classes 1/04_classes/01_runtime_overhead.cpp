struct MyStruct {
    int a; // Default visibility: public
};

class MyClass {
    int a; // Default visibility: private
};


struct MyStruct {
    virtual void foo() {} // Adds runtime overhead
    int x, y; // visible
};

class MyClass {
    virtual void foo() {} // Adds runtime overhead
    int x, y; // private
};
