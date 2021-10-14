#include <iostream>
#include <utility>


struct MyStruct
{
    inline MyStruct() : a(0), b(0), c(0)
    {
        std::cout << "MyStruct constructor called" << std::endl;
    }

    inline MyStruct(const MyStruct& other)
    {
        a = other.a;
        b = other.b;
        c = other.c;
        std::cout << "MyStruct copy constructor called" << std::endl;
    }

    inline MyStruct(MyStruct&& other)
    {
        a = std::exchange(other.a, 0);
        b = std::exchange(other.b, 0);
        c = std::exchange(other.c, 0);
        //a = std::move(other.a);
        //b = std::move(other.b);
        //c = std::move(other.c);
        std::cout << "MyStruct copy constructor called" << std::endl;
    }

    MyStruct& operator=(const MyStruct& other)
    {
        a = other.a;
        b = other.b;
        c = other.c;
        return *this;
    }

    MyStruct& operator=(MyStruct&& other)
    {
        a = std::move(other.a);
        b = std::move(other.b);
        c = std::move(other.c);
        return *this;
    }

    int a;
    int b;
    int c;
};

class MyClass
{
public:
    MyStruct get_mystruct() { return mystruct;}
    MyStruct get_mystruct_cst() const { return mystruct;}
    const MyStruct& get_mystruct_ref() const { return mystruct;}
private:
    MyStruct mystruct;
};



int main()
{
    std::cout << "Constructing myclass object" << std::endl;
    MyClass myclass;
    std::cout << std::endl;

    std::cout << "Constructing toto object" << std::endl;
    MyStruct toto = myclass.get_mystruct();
    std::cout << std::endl;

    std::cout << "Constructing tata object" << std::endl;
    const MyStruct& tata = myclass.get_mystruct_ref();
    std::cout << std::endl;

    std::cout << "Constructing titi object" << std::endl;
    MyStruct titi = myclass.get_mystruct_cst();
    std::cout << std::endl;

    return 0;
}