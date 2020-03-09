#include <iostream>
#include "AbstractC.hpp"


class C : AbstractC
{
public :
    inline void init() override
    {
        std::cout << "Hello from C!" << std::endl;
    }
};


int main()
{
    C c;
    c.init();
    return 0;
}

