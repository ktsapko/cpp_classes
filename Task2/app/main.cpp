#include "../src/SimpleXmlParser.h"
#include "../src/BufferWriter.h"
#include "../src/BufferReader.h"

#include <iostream>
#include <string_view>
#include <variant>
#include <vector>
#include <charconv>
#include <system_error>

int main()
{
    std::string_view xml =
        "<data>"
        "<field1 type=\"int\">12333</field1>"
        "<field2 type=\"string\">abcd</field2>"
        "</data>";

    SimpleXmlParser SimpleXmlParser;
    auto fields = SimpleXmlParser.parse(xml);

    auto buffer =
        BufferWriter::write(fields);

    BufferReader::dump(buffer);

    return 0;
}
