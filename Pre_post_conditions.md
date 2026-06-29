# 3. Preconditions and Postconditions

## Question
**Should preconditions and postconditions be used in functions?**

### Correct answer
**Yes, whenever it is possible.**

## Introduction

Preconditions and postconditions describe the **contract** of a function.

A function should clearly define:

- what **must be true before** it is called;
- what **will be true after** it finishes successfully.

This idea is known as **Design by Contract**.

## Why do they exist?

Imagine a function

```cpp
void divide(int a, int b);
```

Can we call

```cpp
divide(10, 0);
```

Nothing in the declaration tells us.

The function has an implicit requirement.

That requirement is called a **precondition**.

## Precondition

A precondition is something the **caller must guarantee** before calling a function.

Example

```cpp
double divide(double a, double b);
```

Precondition

```text
b != 0
```

If the caller violates the precondition,

the function is not responsible for producing a meaningful result.

## Example

```cpp
double divide(double a, double b)
{
    assert(b != 0);

    return a / b;
}
```

The caller must satisfy

```text
b != 0
```

before calling.

## Another example

```cpp
std::string getFirst(
    const std::vector<std::string>& data);
```

Precondition

```text
data is not empty
```

Otherwise

```cpp
data.front();
```

is Undefined Behavior.

## Postcondition

A postcondition is something the **function guarantees** after successful execution.

Example

```cpp
void sort(std::vector<int>& data);
```

Postcondition

```text
The vector is sorted.
```

The caller no longer needs to check whether sorting happened.

The contract guarantees it.

## Example

```cpp
void push(int value);
```

Postcondition

```text
Container size increased by one.
```

## Preconditions vs Validation

Sometimes a function validates input.

```cpp
bool login(
    const std::string& user,
    const std::string& password);
```

Here invalid credentials are **normal business logic**.

No precondition exists.

Instead the function returns

```cpp
false
```

Contrast this with

```cpp
std::vector<int>::operator[]
```

Precondition

```text
index < size()
```

Violating it is a programming error.

## Assertions

Preconditions are often checked using

```cpp
assert(...)
```

Example

```cpp
void setAge(int age)
{
    assert(age >= 0);

    m_age = age;
}
```

Assertions help detect programmer mistakes during development.

## Exceptions

Some libraries enforce preconditions with exceptions.

```cpp
if (b == 0)
{
    throw std::invalid_argument(
        "Division by zero");
}
```

Others simply document the requirement.

The choice depends on the project.

## Your project

Example from your integration tests

```cpp
client.connect();
```

Possible preconditions

```text
Certificates exist.
Environment variables are loaded.
Network is available.
Client object is initialized.
```

Postcondition

```text
Connection is established.
```

or

```text
Function returned false.
```

Another example

```cpp
OracleClient::executeQuery(sql);
```

Preconditions

```text
Connection is open.
SQL string is valid.
```

Postcondition

```text
Result set is available.
```

## Why contracts matter

Without contracts

```cpp
foo();
```

raises many questions.

Can it receive nullptr?

Can it receive an empty vector?

Can it throw?

Can it modify the object?

With good contracts,

all these questions are answered.

## Interview Questions

**Q:** What is a precondition?

**A:** A requirement that must be satisfied before calling a function.

**Q:** Who is responsible for satisfying a precondition?

**A:** The caller.

**Q:** What is a postcondition?

**A:** A guarantee provided by the function after successful completion.

**Q:** What is Design by Contract?

**A:** A programming methodology where functions define clear obligations and guarantees.

## Best Practices

- Document important preconditions.
- Use `assert()` for programmer errors.
- Validate user input separately from preconditions.
- Keep postconditions simple and predictable.
- Make function contracts obvious from the interface.

## Remember

> Preconditions describe what the **caller must guarantee**.

> Postconditions describe what the **function guarantees**.

A well-designed function should have a clear contract that makes incorrect usage difficult and correct usage obvious.
