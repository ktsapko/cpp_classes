# Modern C++ Engineering Handbook
## Part I. Language Fundamentals
# 1. const_cast

## Question
**What is `const_cast<>` used for?**

### Correct answer
Adding or removing `const` (or `volatile`) qualifiers.

## Introduction
`const_cast` is one of the four C++ cast operators.

```cpp
static_cast
dynamic_cast
reinterpret_cast
const_cast
```
Its only purpose is to add or remove `const` or `volatile`.
It **does not change the object type**.

## Syntax
```cpp
const_cast<new_type>(expression)
```

Example:

```cpp
const int* p = &value;
int* ptr = const_cast<int*>(p);
```

## Example

```cpp
int value = 10;
const int* p = &value;
int* ptr = const_cast<int*>(p);
*ptr = 20;
```

This is safe because `value` itself is **not const**.

## Undefined Behavior

```cpp
const int value = 10;
int* ptr = const_cast<int*>(&value);
*ptr = 20;
```

The program now has **Undefined Behavior**.

## Typical mistakes

- Thinking `const_cast` changes object type.
- Modifying an object originally declared `const`.
- Using `const_cast` to fix poor API design.

## Interview

**Q:** Can `const_cast` change object type?

**A:** No.

**Q:** When is it safe?

**A:** Only if the original object was not declared `const`.

## Best Practices

- Prefer const-correct APIs.
- Avoid `const_cast` in application code.
- Never use it to bypass poor design.

## Remember

> `const_cast` changes qualifiers, **not object types**.
