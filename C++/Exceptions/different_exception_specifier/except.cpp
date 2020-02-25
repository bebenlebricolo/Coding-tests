#include <iostream>
#include <string>
#include <exception>

struct MyException : public std::exception
{
public:
    MyException(){}
    std::string what()
    {
        return "MyException was thrown !! ";
    }
};


void throw_MyException(void) throw(std::exception)
{
    throw MyException();
}


int main()
{

    try
    {
        throw_MyException();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    return 0;
}