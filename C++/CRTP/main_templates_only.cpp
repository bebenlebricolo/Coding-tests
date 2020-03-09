#include <iostream>

struct Base_static
{
    void print_tata()
    {
        std::cout << "Tata from Base_static" << std::endl;
    }
};

struct D : Base_static
{
    void print_tata()
    {
        std::cout << "Tata from D" << std::endl;
    }
};

struct E : Base_static
{
    void print_tata()
    {
        std::cout << "Tata from E" << std::endl;
    }
};

template<class Base>
void print_tata(Base& b)
{
    b.print_tata();
}

int main()
{
    Base_static bs;
    D d;
    E e;
    print_tata<Base_static>(bs);
    print_tata<D>(d);
    print_tata<E>(e);

    return 0;
}