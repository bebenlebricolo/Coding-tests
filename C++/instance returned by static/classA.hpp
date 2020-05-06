#ifndef CLASSA_HEADER
#define CLASSA_HEADER

#include <string>
#include <iostream>

class A
{
public:
    A(std::string p_msg) : msg(p_msg)
    {}
    A(A& other) = delete;
    static A build_simple_A(const std::string& a)
    {
        return A(a);
    }
    void print() const {std::cout << msg << std::endl;}
private:
    std::string msg;
};

#endif