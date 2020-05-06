#include "classA.hpp"

int main()
{
    auto a = A::build_simple_A("Hello World!");
    a.print();
    return 0;
}