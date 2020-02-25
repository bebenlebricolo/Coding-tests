#ifndef _MOCK_CURRENT_SENSOR_HEADER_
#define _MOCK_CURRENT_SENSOR_HEADER_

#include <vector>
#include <cstdint>
#include "AbstractSensor.hpp"



namespace electrical
{

class MockCurrentSensor : public AbstractSensor
{
public:
    MockCurrentSensor() = delete;
    MockCurrentSensor(std::vector<int32_t> &_values) : values(_values){}

    int32_t read() override
    {
        auto fake_reading = values[index];
        index++;
        index %= values.size();
        return fake_reading;
    }
private:
    std::vector<int32_t> values;
    uint32_t index = 0;
};



}

#endif /* _MOCK_CURRENT_SENSOR_HEADER_ */