#include "y_stack.h"
#include <iostream>

int main() {
    stack myStack;

    myStack.push(10);
    myStack.push(20);
    myStack.push(30);

    std::cout << "�˵� ��: " << myStack.pop() << std::endl;
    std::cout << "�˵� ��: " << myStack.pop() << std::endl;

    myStack.push(40);

    std::cout << "�˵� ��: " << myStack.pop() << std::endl;
    std::cout << "�˵� ��: " << myStack.pop() << std::endl;
}
