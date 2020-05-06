#include "classA.hpp"
#include "classB.hpp"

int main()
{
    A a;
    B b;
    a.calling_b_from_a();
    b.calling_a_from_b();
    return 0;
}