cmake_minimum_required(VERSION 3.20)

project(XmlParser)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(XmlParser
    app/main.cpp
    src/SimpleXmlParser.cpp
    src/BufferReader.cpp
    src/BufferWriter.cpp
)