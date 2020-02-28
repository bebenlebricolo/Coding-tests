#ifndef _CLASS_B_HEADER_
#define _CLASS_B_HEADER_

#include <iostream>
#include <string>


#ifdef FORWARD_DECLARE_A
template <typename T>
class A;
#else
    #include "classA.hpp"
#endif

template <typename T>
class B
{
public:
    B(A<T>& _a) : parent(_a) {}
    void do_something(T& p_arg)
    {
        std::cout << "Hello from B with arg = " << std::to_string(p_arg) << std::endl;
        std::cout << "B needs A.member 1 = " << std::to_string(parent.member1) << std::endl;
        std::cout << "B needs A.member 2 = " << std::to_string(parent.member2) << std::endl;
        parent.only_B_can_access_this();
    }
private:
    A<T>& parent;
};

#endif /* _CLASS_A_HEADER_ */