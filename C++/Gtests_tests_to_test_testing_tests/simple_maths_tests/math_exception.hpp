#ifndef _MATHS_EXCEPTION_HEADER_
#define _MATHS_EXCEPTION_HEADER_

#include <string>

namespace exceptions
{

struct MathException
{
    MathException(std::string msg) : msg(msg) {}
    std::string what() {return msg;}
private:
    std::string msg;
};


struct CannotDivideByZero : public MathException
{
    CannotDivideByZero(std::string msg) : MathException(msg) {}
};

}



#endif /* _MATHS_EXCEPTION_HEADER_ */