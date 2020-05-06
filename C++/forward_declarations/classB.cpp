#include <iostream>
#include "classB.hpp"

B::B()
{
    std::cout << "Created B!" << std::endl;
}

void B::printmsg()
{
    std::cout << "B was called !" << std::endl;
}

void B::calling_a_from_b()
{
    a->printmsg();
}