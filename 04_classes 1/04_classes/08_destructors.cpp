// Resource Without Its Own Destructor
class FileWrapper {
    FILE* file;

public:
    FileWrapper(const char* filename) : file(fopen(filename, "r")) {}
    ~FileWrapper() { if (file) fclose(file); }
};

// Class Acting as a Destructor Wrapper
class Cleanup {
    std::function<void()> on_destruct;

public:
    explicit Cleanup(std::function<void()> func) : on_destruct(func) {}
    ~Cleanup() { on_destruct(); }
};

// If a move constructor or move assignment operator is explicitly defined, the compiler does not automatically generate a destructor.
class MyClass {
    std::vector<int> data;

public:
    MyClass(MyClass&& other) noexcept : data(std::move(other.data)) {}

    // Explicitly default the destructor
    ~MyClass() = default;
};