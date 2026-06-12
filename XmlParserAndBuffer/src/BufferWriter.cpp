#include "BufferWriter.h"
#include "FieldEntry.h"

#include <cstring>
#include <iostream>
#include <string_view>

std::vector<std::byte> BufferWriter::write(const std::vector<Field> &fields)
{

    uint32_t count = fields.size();

    size_t totalSize =
        sizeof(uint32_t) +
        count * sizeof(FieldEntry);

    for (const auto &field : fields) // Calculate total size of the buffer
    {
        totalSize += field.name.size();

        if (std::holds_alternative<int>(field.value))
        {
            totalSize += sizeof(int);
        }
        else
        {
            totalSize +=
                std::get<std::string_view>(
                    field.value)
                    .size();
        }
    }

    std::vector<std::byte> buffer(totalSize); // Allocate memory for the whole buffer

    auto *data = buffer.data();

    std::memcpy(data, &count, sizeof(count));

    auto *entries =
        reinterpret_cast<FieldEntry *>(
            data + sizeof(uint32_t));

    size_t writePos =
        sizeof(uint32_t) +
        count * sizeof(FieldEntry);

    for (size_t i = 0; i < fields.size(); ++i)
    {
        const auto &field = fields[i];

        entries[i].nameOffset = writePos;
        entries[i].nameLength = field.name.size();

        std::memcpy(
            data + writePos,
            field.name.data(),
            field.name.size());

        writePos += field.name.size();

        if (std::holds_alternative<int>(field.value))
        {
            entries[i].valueType = FieldType::Int;

            int value =
                std::get<int>(field.value);

            entries[i].valueOffset = writePos;
            entries[i].valueLength = sizeof(int);

            std::memcpy(
                data + writePos,
                &value,
                sizeof(int));

            writePos += sizeof(int);
        }
        else
        {
            entries[i].valueType = FieldType::String;

            auto value =
                std::get<std::string_view>(
                    field.value);

            entries[i].valueOffset = writePos;
            entries[i].valueLength = value.size();

            std::memcpy(
                data + writePos,
                value.data(),
                value.size());

            writePos += value.size();
        }
    }
    return buffer;
}