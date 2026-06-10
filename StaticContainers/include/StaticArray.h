#pragma once

#include <cstddef>
#include <stdexcept>

template<typename T, std::size_t N>
class StaticArray
{
public:
    T& at(std::size_t index)
    {
        if (index >= N)
        {
            throw std::out_of_range("Index out of range");
        }

        return m_data[index];
    }

    const T& at(std::size_t index) const
    {
        if (index >= N)
        {
            throw std::out_of_range("Index out of range");
        }

        return m_data[index];
    }

    constexpr std::size_t size() const noexcept
    {
        return N;
    }

private:
    T m_data[N]{};
};