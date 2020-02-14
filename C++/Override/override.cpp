#include <iostream>
#include <memory>
#include <cassert>

class A
{
private:
    int _inner;
public:
    void virtual say_hello() const
    {
        std::cout << "Hello from A!" << std::endl;
    }

    A()=delete;
    virtual ~A(){};
    explicit A(int a) :_inner(a) {
        std::cout << "Building A with parameter : " << a << std::endl;
    }
    virtual int get_inner(){return _inner;}
};


class B : public A
{
private:
    int _bInner;
public:
    //void virtual say_hello() override;      // will not compile unless it matches exactly A::say_hello signature
    void virtual say_hello() const
    {
        std::cout << "Hello from B!" << std::endl;
    }
    ~B(){};
    explicit B(int b) : A(b),_bInner(b*12){
        std::cout << "Building B with parameter : " << b*12 << std::endl;
    }
    int get_bInner() {return _bInner;}
};

int main(int argc, char **argv)
{
    //A a; // Will normally fail
    A a(35);
    B b(25);
    A* toto = new B(12);

    assert(a.get_inner() == 35);
    assert(b.get_inner() == 25);
    assert(b.get_bInner() == (12*25));
    assert(toto->get_inner() == 12);
    assert(dynamic_cast<B*>(toto)->get_bInner() == (12*12));

    a.say_hello();
    b.say_hello();
    toto->say_hello();

    delete toto;

    return 0;
}