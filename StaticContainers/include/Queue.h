#pragma once

#include "StaticArray.h"

#include <vector>
#include <stdexcept>
#include <cstddef>

template<typename T, std::size_t N>
class Queue
{
public:
    Queue() = default;

    void push(const T& value)
    {
        if (full())
        {
            throw std::overflow_error("Queue overflow");
        }

        m_storage.at(m_tail) = value;

        m_tail = (m_tail + 1) % N;

        ++m_count;
    }

    T pop()
    {
        if (empty())
        {
            throw std::underflow_error("Queue underflow");
        }

        T value = m_storage.at(m_head);

        m_head = (m_head + 1) % N;

        --m_count;

        return value;
    }

    bool empty() const noexcept
    {
        return m_count == 0;
    }

    bool full() const noexcept
    {
        return m_count == N;
    }

    std::size_t size() const noexcept
    {
        return m_count;
    }

    std::size_t capacity() const noexcept
    {
        return N;
    }

private:
    StaticArray<T, N> m_storage;

    std::size_t m_head{0};
    std::size_t m_tail{0};
    std::size_t m_count{0};
};