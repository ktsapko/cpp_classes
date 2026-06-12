#pragma once

#include <cstdint>

enum class FieldType : uint8_t
{
    Int,
    String
};

struct FieldEntry
{
    uint32_t nameOffset;
    uint32_t nameLength;

    uint32_t valueOffset;
    uint32_t valueLength;

    FieldType valueType;
};