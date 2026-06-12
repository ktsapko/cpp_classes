#pragma once

#include <memory>
#include <string_view>
#include <unordered_map>

class Trie
{
public:
    void insert(std::string_view word);

    bool contains(std::string_view word) const;

    bool startsWith(std::string_view prefix) const;

private:
    struct Node
    {
        bool isEndOfWord{false};

        std::unordered_map<char, std::unique_ptr<Node>> children;
    };

    Node root;
};