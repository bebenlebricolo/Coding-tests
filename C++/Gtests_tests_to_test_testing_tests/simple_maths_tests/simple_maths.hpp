#ifndef _SIMPLE_MATHS_HEADER_
#define _SIMPLE_MATHS_HEADER_

#include <cstdint>
#include "math_exception.hpp"

namespace SimpleMaths
{

template<typename T>
T add(T a, T b)
{
    return a + b;
}

template<typename T>
T substract(T a, T b)
{
    return a - b;
}

template<typename T>
T multiply(T a, T b)
{
    return a * b;
}

template<typename T>
T divide(T a, T b)
{
    if (b == 0)
    {
        throw exceptions::CannotDivideByZero("cannot divide a" + std::to_string(a) + " by 0 !");
    }
    return a / b;
}

template<typename T>
T modulo(T a, T b)
{
    return a % b;
}

}
#endif /* _SIMPLE_MATHS_HEADER_ */