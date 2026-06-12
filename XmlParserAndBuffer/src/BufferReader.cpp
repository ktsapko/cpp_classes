#include "BufferReader.h"
#include "FieldEntry.h"

#include <cstring>
#include <iostream>
#include <string_view>

void BufferReader::dump(
    const std::vector<std::byte> &buffer)
{
    const auto *data = buffer.data();

    uint32_t count{0};

    std::memcpy(
        &count,
        data,
        sizeof(count));

    auto *entries =
        reinterpret_cast<const FieldEntry *>(
            data + sizeof(uint32_t));

    for (uint32_t i = 0; i < count; ++i)
    {
        const auto &entry = entries[i];

        std::string_view name(
            reinterpret_cast<const char *>(
                data + entry.nameOffset),
            entry.nameLength);

        std::cout << name << " = ";

        if (entry.valueType == FieldType::Int)
        {
            int value;

            std::memcpy(
                &value,
                data + entry.valueOffset,
                sizeof(int));

            std::cout << value;
        }
        else
        {
            std::string_view value(
                reinterpret_cast<const char *>(
                    data + entry.valueOffset),
                entry.valueLength);

            std::cout << value;
        }

        std::cout << '\n';
    }
}