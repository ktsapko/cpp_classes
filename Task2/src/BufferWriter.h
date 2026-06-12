#pragma once

#include "SimpleXmlParser.h"

#include <vector>
#include <cstddef>

class BufferWriter
{
public:
    static std::vector<std::byte>
    write(const std::vector<Field> &fields);
};