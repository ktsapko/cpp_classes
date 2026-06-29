# 2. Exceptions

## Question
**Is it allowed to use exceptions?**

### Correct answer
**Yes, if there are no additional project restrictions.**

## Introduction

Exceptions are C++'s built-in mechanism for reporting errors.

Instead of returning an error code, a function can **throw** an object describing the error.

Another part of the program can **catch** it and decide how to recover.

## Why do exceptions exist?

Without exceptions developers often write

```cpp
bool connect();
```

or

```cpp
ErrorCode parse();
```

Every function call must then be checked.

```cpp
if (!connect())
{
    return false;
}

if (!login())
{
    return false;
}

if (!download())
{
    return false;
}
```

This quickly clutters the code.

Exceptions separate the **normal execution path** from the **error handling path**.

## Basic syntax

Throwing an exception:

```cpp
throw std::runtime_error("Cannot open file");
```

Handling an exception:

```cpp
try
{
    loadConfiguration();
}
catch(const std::exception& ex)
{
    std::cout << ex.what();
}
```

## Example 1

Without exceptions

```cpp
bool readFile()
{
    if (!open())
        return false;

    if (!parse())
        return false;

    return true;
}
```

With exceptions

```cpp
void readFile()
{
    open();
    parse();
}
```

If something fails

```cpp
throw std::runtime_error("Parse error");
```

The caller handles it.

```cpp
try
{
    readFile();
}
catch(...)
{
    std::cout << "Failed";
}
```

## Example 2 — STL

Many STL functions throw exceptions.

```cpp
std::vector<int> data;

data.at(100);
```

throws

```cpp
std::out_of_range
```

instead of returning an error code.

## Exception hierarchy

Most standard exceptions derive from

```cpp
std::exception
```

Examples

```cpp
std::runtime_error
std::logic_error
std::invalid_argument
std::out_of_range
std::bad_alloc
```

Because of inheritance

```cpp
catch(const std::exception& ex)
```

can catch all of them.

## RAII and exceptions

One of the biggest advantages of exceptions is automatic resource cleanup.

```cpp
void foo()
{
    std::vector<int> data;

    throw std::runtime_error("error");
}
```

Even though an exception is thrown,

`data` is destroyed automatically.

This is why RAII is so important.

## Exception safety

Well-written C++ code guarantees that resources are not leaked even when exceptions occur.

Example

```cpp
std::unique_ptr<Client> client =
    std::make_unique<Client>();

client->connect();

throw std::runtime_error("Error");
```

The memory is still released.

## Advantages

- Cleaner happy path.
- Automatic cleanup through RAII.
- Centralized error handling.
- Rich hierarchy of error types.
- Error information can propagate through many function calls.

## Disadvantages

- Harder control flow.
- Runtime overhead when exceptions are thrown.
- Some projects disable them.
- Requires understanding of exception safety.

## Where exceptions are forbidden

Many embedded and safety-critical projects compile with

```text
-fno-exceptions
```

Examples

- Automotive
- Aerospace
- Medical devices
- Real-time systems

Instead they use

```cpp
bool connect();
```

or

```cpp
enum class ErrorCode
{
    Ok,
    ConnectionFailed,
    Timeout
};
```

## Your project

Your integration test project uses

```cpp
if (!client.connect())
{
    return false;
}
```

instead of

```cpp
client.connect();
```

throwing an exception.

This is common for networking libraries.

## Interview Questions

**Q:** What is an exception?

**A:** An object representing an error that interrupts normal execution.

**Q:** What keyword throws an exception?

**A:** `throw`

**Q:** What keywords handle exceptions?

**A:** `try` and `catch`

**Q:** Why is RAII important with exceptions?

**A:** Resources are released automatically during stack unwinding.

**Q:** Why do some companies disable exceptions?

**A:** Predictability, binary size, certification requirements and deterministic execution.

## Best Practices

- Throw exceptions only for exceptional situations.
- Catch exceptions by `const&`.
- Derive custom exceptions from `std::exception`.
- Never throw from a destructor.
- Use RAII to manage resources.

## Remember

> Exceptions separate normal execution from error handling.

> RAII makes exceptions safe.

> Some projects (MISRA, AUTOSAR, embedded) disable exceptions completely.
