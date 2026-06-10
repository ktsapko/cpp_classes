# Modern C++ Course

This repository contains my learning materials, homework tasks, experiments, and practice code from the Modern C++ course.

## Purpose

The goal of this repository is to track my progress in learning C++ as a software development language, with focus on:

* C++ language fundamentals
* Object-oriented programming
* Templates
* RAII and resource management
* STL containers and algorithms
* Memory management
* Pointers and references
* Static and dynamic arrays
* Stack and queue implementations
* Circular buffers
* Unit testing
* CMake-based project structure

## Repository Structure

```text
.
├── app/              # Application entry points and examples
├── include/          # Header files
├── src/              # Source files
├── tests/            # Unit tests
├── CMakeLists.txt    # CMake configuration
└── README.md
```

## Topics Covered

### Static Containers

Implementation of basic container-like structures over a fixed-size static array:

* `StaticArray`
* `Stack`
* `Queue`
* Circular buffer logic
* `push()` / `pop()` operations
* Internal state inspection
* Error handling

### C++ Concepts Practiced

* Classes and constructors
* Templates
* Header-only template implementation
* `std::initializer_list`
* `const` correctness
* References
* `size_t`
* `noexcept`
* Encapsulation
* Separation of interface and implementation
* Build and linker errors investigation

## Build

```bash
cmake -S . -B build
cmake --build build
```

Or with Ninja:

```bash
cmake -S . -B build -G Ninja
cmake --build build
```

## Run

```bash
./build/StaticContainers
```

## Notes

This repository is mainly educational.
Code here may be rewritten and improved as new C++ concepts are learned during the course.

The main focus is not only to make the code work, but also to understand how C++ works under the hood.
