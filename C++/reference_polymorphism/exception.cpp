#include <iostream>
#include <string>

using namespace std;

class Base
{
public:
    virtual inline const char* get_class_name() const {return "Base";}
};

class Derived : public Base
{
public:
    virtual inline const char* get_class_name() const override {return "Derived";}
};

void foo(Base& b)
{
    cout << "This is class : " << b.get_class_name() << endl;
}

int main(int argc, char ** argv)
{
    Base b;
    Derived d;

    // Using polymorphism with references
    foo(b);         // Prints out "Base"
    foo(d);         // Prints out "Derived"

    return 0;
}