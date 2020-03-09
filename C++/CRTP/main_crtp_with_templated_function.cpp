#include <iostream>

template<typename T>
struct crtp
{
    T& underlying() {return static_cast<T&>(*this);}
    const T& underlying() const {return static_cast<const T&>(*this);}
};

template<typename T>
struct Base2 : public crtp<T>
{
    void say_hello_from_Base2()
    {
        std::cout << "Hello from Base2 " << std::endl;
        this->underlying().say_hello_from_Base2();
    }
};

struct DerivedfromBased2_1 : public Base2<DerivedfromBased2_1>
{
    void say_hello_from_Base2()
    {
        std::cout << "Hello from DerivedfromBase2_1 " << std::endl; // This shall never be called
    }
};

template<typename T>
void do_something_with_base_2_children(T& t)
{
    t.say_hello_from_Base2();
}



int main()
{
    DerivedfromBased2_1 d3;
    DerivedfromBased2_1 d4;
    d3.say_hello_from_Base2();
    d4.say_hello_from_Base2();
    do_something_with_base_2_children<DerivedfromBased2_1>(d3);

    return 0;
}