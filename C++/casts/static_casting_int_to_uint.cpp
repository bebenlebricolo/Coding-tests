#include <iostream>
#include <string>
using namespace std;

#include <tuple>

class Other
{};

class Base
{
public:
    virtual void foo() {}

    void bar()
    {
        std::cout << "Check !" << std::endl;
    }
};

class Derived : public Base
{
public:
    void foo()
    {
        std::cout << "Derived" << std::endl;
    }
};

class Derived2 : public Base
{
public:

    void bar()
    {
        std::cout << "Derived2" << std::endl;
    }
};


int main(void)
{
    std::tuple<int, char, std::string, std::string, char> super_list;
    Base base;
    Derived derived;
    Base* real_derived = &derived;
    auto cast_derived = dynamic_cast<Derived*>(real_derived);
    auto cast_other = dynamic_cast<Other*>(real_derived);
    auto static_other = static_cast<Other>(derived);
    base.foo();
    derived.foo();
    real_derived->foo();
    return 0;
}