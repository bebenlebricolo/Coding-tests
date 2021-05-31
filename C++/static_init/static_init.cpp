#include <iostream>

class toto
{
    static bool hello();
    static bool initialized;
};

bool hello2()
{
    std::cout << "Hello from hello2" << std::endl;
    return true;
}

bool toto::hello()
{
    std::cout << "Hello from hello" << std::endl;
    return true;
}

//bool toto::initialized = toto::hello();
bool toto::initialized = hello2();

int main()
{
    return 0;
}