#ifndef _CLASS_A_HEADER_
#define _CLASS_A_HEADER_

#include "classB.hpp"

template <typename T>
class A
{
public:
    A() : b(*this) {}
    void do_something(T& p_arg)
    {
        std::cout << "Hello from A with arg = " << std::to_string(p_arg) << std::endl;
        b.do_something(p_arg);
    }
private:
    friend B<T>;
    void only_B_can_access_this()
    {
        std::cout << "Called by B !" << std::endl;
    }
    B<T> b;
    T member1 = 33;
    T member2 = 36;
};

#endif /* _CLASS_A_HEADER_ */