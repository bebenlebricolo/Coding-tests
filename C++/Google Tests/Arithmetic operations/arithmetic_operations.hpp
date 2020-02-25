#ifndef _ARITHMETIC_OPERATIONS_HEADER_
#define _ARITHMETIC_OPERATIONS_HEADER_

template<typename T>
class Operations
{
public:
    T add() { return a + b; };
    T substrac() {return a - b};
    T multiply() {return a * b};
    T divide()  {return a / b};
private:
    T a;
    T b;
};

#endif /* _ARITHMETIC_OPERATIONS_HEADER_ */