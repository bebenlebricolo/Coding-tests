#ifndef _CLASS_B_HEADER_
#define _CLASS_B_HEADER_

#include <iostream>
#include <string>

// Forward declare A
// Because B is included by A at the beginning of the file, B would know about A
// and as the effective A declaration occurs in the same file, our compiler will be
// able to reconnect everyting
template <typename T>
class A;

// Template declaration
template <typename T>
class B
{
public:
    B(A<T>& _a);
    void do_something(T& p_arg);
private:
    A<T>& parent;
};


// Class B template-definition
template <typename T>
B<T>::B(A<T>& _a) : parent(_a)
{}

template <typename T>
void B<T>::do_something(T& p_arg)
{
    std::cout << "Hello from B with arg = " << std::to_string(p_arg) << std::endl;
    std::cout << "B needs A.member 1 = " << std::to_string(parent.member1) << std::endl;
    std::cout << "B needs A.member 2 = " << std::to_string(parent.member2) << std::endl;
    parent.only_B_can_access_this();
}


#endif /* _CLASS_A_HEADER_ */