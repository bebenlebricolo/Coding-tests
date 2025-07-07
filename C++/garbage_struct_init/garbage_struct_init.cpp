#include <stdlib.h>
#include <cstdint>
#include <iostream>
#include <string>

struct Test
{
    inline void print()
    {
        std::cout << "double b : "<< std::to_string(b) << std::endl
                  << "int a : " << std::to_string(a) << std::endl
                  << "char c : " << std::to_string(c) << std::endl
                  << "unsigned int d : " << std::to_string(d) << std::endl << std::endl;
    }

    double b;
    int a;
    char c;
    unsigned int d;
};

int main()
{
    constexpr uint8_t testsize = sizeof(Test);
    std::cout << "test size is : " << std::to_string(testsize) << " bytes wide " << std::endl;
    Test test;
    test.print();

    uint8_t* start = reinterpret_cast<uint8_t*>(&test);
    std::cout << "Printing test structure byte by byte : " << std::endl;
    for (uint8_t i = 0 ; i < testsize ; i++)
    {
        char buffer[5] = {0};
        std::cout << std::to_string(start[i]) << " ";
    }
    std::cout << std::endl;

    return 0;
}