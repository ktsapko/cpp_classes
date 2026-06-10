#pragma once

#include "StaticArray.h"
#include <initializer_list>

template<typename T, std::size_t N>
class Stack
{
public:
    Stack() = default;

    Stack(std::initializer_list<T> values)
    {
        for (const auto& value : values)
        {
            push(value);
        }
    }
    void push(const T& value)
    {
        if (m_top >= N)
        {
            throw std::overflow_error("Stack overflow");
        }

        m_storage.at(m_top++) = value;
    }

    T pop()
    {
        if (m_top == 0)
        {
            throw std::underflow_error("Stack underflow");
        }

        return m_storage.at(--m_top);
    }

private:
    StaticArray<T, N> m_storage;
    std::size_t m_top{0};
};