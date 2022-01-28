#include <stdlib.h>
#include <cstdint>
#include <cassert>
#include <iostream>
#include <string>

struct Test
{
    double b;
    int a;
    char c;
    unsigned int d;
};

int main()
{
    constexpr uint8_t testsize = sizeof(Test);
    Test test;
    uint8_t* start = reinterpret_cast<uint8_t*>(&test);
    for (uint8_t i = 0 ; i < testsize ; i++)
    {
        char buffer[5] = {0};
        std::cout << std::to_string(start[i]) << " ";
    }
    std::cout << std::endl;

    return 0;
}