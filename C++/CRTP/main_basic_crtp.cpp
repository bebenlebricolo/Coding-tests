#include <iostream>

template<typename T>
struct crtp
{
    T& underlying() {return static_cast<T&>(*this);}
    const T& underlying() const {return static_cast<const T&>(*this);}
};

template <typename T>
struct Base : public crtp<T>
{
    T& Self() {return static_cast<T&>(*this);}
    void say_hello()
    {
       Self().say_hello();
    }
};

struct Derived1 : public Base<Derived1>
{
    void say_hello()
    {
        std::cout << "Hello from Derived 1 " << std::endl;
    }
};

struct Derived2 : public Base<Derived2>
{
    void say_hello()
    {
        std::cout << "Hello from Derived 2 " << std::endl;
    }
};

// Static polymorphism implies that you use this template
// with a class implementing say_hello_from_child
// And we already know, when we use it, that we are using the Derived's implementation
// instead of Base's
template<class T>
void dosmthg(Base<T>& b)
{
    b.say_hello();
}

int main()
{
    Base<Derived1> d0;
    Derived1 d1;
    Derived2 d2;
    dosmthg<Derived1>(d1);
    dosmthg<Derived2>(d2);
    dosmthg<Derived1>(d0);

    return 0;
}