#ifndef _ABSTRACT_C_HEADER_
#define _ABSTRACT_C_HEADER_

#include "AbstractA.hpp"
#include "AbstractB.hpp"

class AbstractC : public AbstractA, public AbstractB
{
public :
    virtual inline void init() override = 0;
};

#endif