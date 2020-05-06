#include "classA.hpp"
#include <iostream>

A::A()
{
    std::cout << "Created A!" << std::endl;
}

void A::printmsg()
{
    std::cout << "A was called !" << std::endl;
}

void A::calling_b_from_a()
{
    b->printmsg();
}

void A::set_b(B& b)
{
    b = std::make_unique<B>(b);
}