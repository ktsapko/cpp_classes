#include <iostream>
#include <string_view>
#include <variant>
#include <vector>
#include <charconv>
#include <system_error>

struct Field
{
    std::string_view name;
    std::variant<int, std::string_view> value;
};

class SimpleXmlParser
{

public:
    std::vector<Field> parse(std::string_view xml)
    {
        std::vector<Field> fields;

        constexpr std::string_view openRootTag = "<data>";
        constexpr std::string_view closeRootTag = "</data>";

        size_t startOfData = xml.find(openRootTag);
        if (startOfData == std::string_view::npos)
            return fields;

        startOfData += openRootTag.size();

        size_t endOfData = xml.find(closeRootTag, startOfData);
        if (endOfData == std::string_view::npos)
            return fields;

        std::string_view body =
            xml.substr(startOfData, endOfData - startOfData);

        size_t pos = 0;

        while (true)
        {
            size_t openStart = body.find('<', pos);
            if (openStart == std::string_view::npos)
                break;

            size_t openEnd = body.find('>', openStart);
            if (openEnd == std::string_view::npos)
                break;

            std::string_view openTag =
                body.substr(openStart + 1, openEnd - openStart - 1);

            size_t spacePos = openTag.find(' ');
            if (spacePos == std::string_view::npos)
                break;

            std::string_view fieldName = openTag.substr(0, spacePos);
            std::string_view type = extractType(openTag);

            std::string closeTagText = "</";
            closeTagText += std::string(fieldName);
            closeTagText += ">";

            size_t closeStart = body.find(closeTagText, openEnd);
            if (closeStart == std::string_view::npos)
                break;

            std::string_view rawValue =
                body.substr(openEnd + 1, closeStart - openEnd - 1);

            if (type == "int")
            {
                int value{};

                if (parseInt(rawValue, value))
                {
                    fields.push_back(Field{fieldName, value});
                }
            }
            else if (type == "string")
            {
                fields.push_back(Field{fieldName, rawValue});
            }

            pos = closeStart + closeTagText.size();
        }

        return fields;
    }

private:
    std::string_view extractType(std::string_view tag)
    {
        std::string_view key = "type=\"";

        size_t start = tag.find(key);
        if (start == std::string_view::npos)
            return {};

        start += key.size();

        size_t end = tag.find('"', start);
        if (end == std::string_view::npos)
            return {};

        return tag.substr(start, end - start);
    }

    bool parseInt(std::string_view text, int &value)
    {
        auto [ptr, ec] = std::from_chars(
            text.data(),
            text.data() + text.size(),
            value);

        return ec == std::errc{} && ptr == text.data() + text.size();
    }
};

int main()
{
    std::string_view xml =
        "<data>"
        "<field1 type=\"int\">123</field1>"
        "<field2 type=\"string\">abc</field2>"
        "</data>";

    SimpleXmlParser parser;

    auto fields = parser.parse(xml);

    for (const auto &field : fields)
    {
        std::cout << field.name << " = ";

        std::visit([](const auto &value)
                   { std::cout << value; }, field.value);

        std::cout << '\n';
    }

    return 0;
}
