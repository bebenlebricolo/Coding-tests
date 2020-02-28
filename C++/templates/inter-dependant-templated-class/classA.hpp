#ifndef _CLASS_A_HEADER_
#define _CLASS_A_HEADER_

#include "classB.hpp"

// What's happening when we include ClassB.hpp :
// classA.hpp
//  includes B
//     forward declares A
//     class B declaration
//          B needs A
//  class A declaration (overrides forward declaration)
//      uses B

// As B and A are both delcared AND defined in the same concatenated header file,
// Our compiler will have all necessary informations to do the adequate plumbing between
// classes A and B, even if at the moment when B is declared and defined, A is not a fully
// qualified type yet (has only been forward declared at this time)

// Class A declaration
template <typename T>
class A
{
public:
    A();
    void do_something(T& p_arg);
private:
    friend B<T>;
    B<T> b;
    void only_B_can_access_this();
    T member1 = 33;
    T member2 = 36;
};

// Class A template-definition
template <typename T>
A<T>::A() : b(*this) {}

template <typename T>
void A<T>::do_something(T& p_arg)
{
    std::cout << "Hello from A with arg = " << std::to_string(p_arg) << std::endl;
    b.do_something(p_arg);
}

template <typename T>
void A<T>::only_B_can_access_this()
{
    std::cout << "Called by B !" << std::endl;
}

#endif /* _CLASS_A_HEADER_ */