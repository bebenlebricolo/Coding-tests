#include <iostream>
#include <string>

class Base
{
public:
    Base():name("Base"){}
    virtual void do_something() = 0;

protected:
    std::string name;
};

class Derived final : public Base
{
public:
    Derived():Base(){name="Derived";}
    void do_something(){std::cout << "Hello from " << name << std::endl;}
};

void do_some_stuff_with_base(Base * b)
{
    b->do_something();
}

int main (int argc, char ** argv)
{
    (void) argc;
    (void) argv;

    {
        Derived d;

        d.do_something();

        // Dynamic polymorphism
        Base * b = &d;
        b->do_something();

        do_some_stuff_with_base(&d);
    }


    return 0;
}