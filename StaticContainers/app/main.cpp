#include <iostream>

#include "Stack.h"
#include "Queue.h"

int main()
{
    std::cout << "=== STACK ===\n";

    Stack<int, 5> stack;

    stack.push(10);
    stack.push(20);
    stack.push(30);

    std::cout << stack.pop() << '\n';
    std::cout << stack.pop() << '\n';
    std::cout << stack.pop() << '\n';

    std::cout << "\n=== QUEUE ===\n";

    Queue<int, 5> queue;

    queue.push(10);
    queue.push(20);
    queue.push(30);

    std::cout << queue.pop() << '\n';
    std::cout << queue.pop() << '\n';
    std::cout << queue.pop() << '\n';

    return 0;
}