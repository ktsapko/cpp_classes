#include <iostream>
#include "Trie.h"

int main()
{
    Trie trie;

    trie.insert("and");
    trie.insert("ant");
    trie.insert("dad");
    trie.insert("do");

    std::cout << std::boolalpha;

    std::cout << "contains(and): "
              << trie.contains("and") << '\n';

    std::cout << "contains(an): "
              << trie.contains("an") << '\n';

    std::cout << "contains(dad): "
              << trie.contains("dad") << '\n';

    std::cout << "contains(cat): "
              << trie.contains("cat") << '\n';

    std::cout << "startsWith(an): "
              << trie.startsWith("an") << '\n';

    std::cout << "startsWith(da): "
              << trie.startsWith("da") << '\n';

    std::cout << "startsWith(ca): "
              << trie.startsWith("ca") << '\n';

    return 0;
}