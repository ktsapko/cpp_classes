#pragma once

#include <string_view>
#include <variant>
#include <vector>

struct Field
{
    std::string_view name;
    std::variant<int, std::string_view> value;
};

class SimpleXmlParser
{
public:
    std::vector<Field> parse(std::string_view xml);

private:
    std::string_view extractType(std::string_view openTag);
    bool parseInt(std::string_view text, int &result);
};