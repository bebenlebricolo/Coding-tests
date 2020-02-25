#include <memory>
#include <iostream>


class toto
{
public:
    toto()
    {
        std::cout << "Building toto" << std::endl;
    }
    void print_hello()
    {
        std::cout << "Hello from toto !" << std::endl;
    }
};

class tata
{
public:
    tata()
    {
        std::cout << "Building tata" << std::endl;
    }
    void set_toto(toto& _to)
    {
        to = &_to;
    }
    void use_toto()
    {
        if (to != nullptr)
            to->print_hello();
    }
private:
    toto * to = nullptr	;
};

class titi
{
public:
    titi(toto& _to) : to(_to)
    {
        std::cout << "Building titi, reference to toto needed to build this object " << std::endl;
    }
private:
    toto& to;
};




int main(int argc, char ** argv)
{
    toto a;
    titi c(a);
    {
        tata b;
        b.use_toto();
    }
    {
        tata b;
        b.set_toto(a);
        b.use_toto();
    }

    return 0;
}