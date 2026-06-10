#include "iostream"




void f(char* name)
{
    FILE* input = fopen(name, "r");
    // ...
    if (something) return;   // bad: if something == true, a file handle is leaked
    // ...
    fclose(input);
}

// Prefer RAII:
void f(char* name)
{
    std::ifstream input {name};
    // ...
    if (something) return;   // OK: no leak
    // ...
}

/*
 * A leak is colloquially “anything that isn’t cleaned up.”
 * The more important classification is:
 * “anything that can no longer be cleaned up.”
 * 
 * For example, allocating an object on the heap and then losing the last 
 * pointer that points to that allocation. This rule should not be taken 
 * as requiring that allocations within long-lived objects must be returned 
 * during program shutdown.
 * 
 * Relying on system-guaranteed cleanup (e.g., file closing and memory 
 * deallocation upon process shutdown) can simplify code. However, relying 
 * on abstractions that implicitly clean up can be just as simple and often safer.
 * 
 * Note:
 * Enforcing the lifetime safety profile eliminates leaks. When combined 
 * with resource safety provided by RAII, it eliminates the need for 
 * “garbage collection” by generating no garbage.
 * 
 * Combine this with enforcement of type and bounds profiles, and you achieve:
 * - Complete type safety
 * - Complete resource safety
 * 
 * These guarantees can be enforced by modern tools.
 */

