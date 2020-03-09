#include <iostream>
#include <string>

template<typename T>
class Base
{
public:
    void do_something()
    {
        std::cout << "Called from Base class " << std::endl;
    }

private:
    friend T;
    Base() : name("Base"){}
    std::string name;
};

class Derived : public Base<Derived>
{
public:
    Derived():Base(){name="Derived";}
    void do_something()
    {
        print_something();
    }
    void print_something(){std::cout << "Hello from Derived" << std::endl;}
};

template<typename T>
void do_some_stuff_with_base(Base<T> * b)
{
    b->do_something();
}

int main (int argc, char ** argv)
{
    (void) argc;
    (void) argv;

    {
        Derived d;

        d.print_something();
        d.do_something();

        // Does not work ! This calls the Base class of Derived, which is not what we actually want
        Base<Derived> * b = &d;
        b->do_something();

        // same goes here
        do_some_stuff_with_base(&d);
    }


    return 0;
}
