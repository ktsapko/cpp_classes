#include <iostream>
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
};