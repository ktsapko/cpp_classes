#include "Trie.h"

void Trie::insert(std::string_view word)
{
    Node* current = &root;

    for (char c : word)
    {
        auto& child = current->children[c];

        if (!child)
        {
            child = std::make_unique<Node>();
        }

        current = child.get();
    }

    current->isEndOfWord = true;
}

bool Trie::contains(std::string_view word) const
{
    const Node* current = &root;

    for (char c : word)
    {
        auto it = current->children.find(c);

        if (it == current->children.end())
        {
            return false;
        }

        current = it->second.get();
    }

    return current->isEndOfWord;
}

bool Trie::startsWith(std::string_view prefix) const
{
    const Node* current = &root;

    for (char c : prefix)
    {
        auto it = current->children.find(c);

        if (it == current->children.end())
        {
            return false;
        }

        current = it->second.get();
    }

    return true;
}