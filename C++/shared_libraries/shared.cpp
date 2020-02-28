#include "shared.hpp"
#include <iostream>


void f()
{
    std::cout << "hello from f!" << std::endl;
}

int g()
{
    std::cout << "hello from g!" << std::endl;
    return -3;
}

const char c()
{
    std::cout << "hello from c!" << std::endl;
    return 'c';
}


toto::toto()
{
    std::cout << "hello from toto!" << std::endl;
}