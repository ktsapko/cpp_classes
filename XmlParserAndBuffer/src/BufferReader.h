#pragma once

#include <vector>
#include <cstddef>

class BufferReader
{
public:
    static void dump(const std::vector<std::byte> &buffer);
};