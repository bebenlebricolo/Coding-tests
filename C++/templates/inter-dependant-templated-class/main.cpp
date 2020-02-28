#include "classA.hpp"


int main(int argc, char **argv)
{
    (void) argc;
    (void) argv;
    A<unsigned int> a;
    unsigned int val = 145;
    a.do_something(val);

    return 0;
}