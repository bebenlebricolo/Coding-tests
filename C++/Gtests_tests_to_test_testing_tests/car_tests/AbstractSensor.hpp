#ifndef _CURRENT_SENSOR_HEADER_
#define _CURRENT_SENSOR_HEADER_

#include <cstdint>

namespace electrical
{

class AbstractSensor
{
public:
    virtual int32_t read() = 0 ;
};

}

#endif /* _CURRENT_SENSOR_HEADER_ */