#ifndef _FUEL_TANK_HEADER_
#define _FUEL_TANK_HEADER_

#include <cstdint>
#include "AbstractSensor.hpp"

namespace mechanical
{

enum class Fuel
{
    gasoline,
    diesel
};

class FuelTank
{
public:
    FuelTank()
    {
        fill_up();
    }
    FuelTank(electrical::AbstractSensor &_fuel_gauge) : fuel_gauge(&_fuel_gauge)
    {
        fill_up();
    }
    FuelTank(uint32_t _capacity,
             uint32_t _remaining_volume,
             Fuel _fuel_type) :
                capacity(_capacity),
                remaining_volume(_remaining_volume),
                fuel_type(_fuel_type)
    {}
    FuelTank(electrical::AbstractSensor &_fuel_gauge,
             uint32_t _capacity,
             uint32_t _remaining_volume,
             Fuel _fuel_type) :
                fuel_gauge(&_fuel_gauge),
                capacity(_capacity),
                remaining_volume(_remaining_volume),
                fuel_type(_fuel_type)
    {}

    bool is_full() {return remaining_volume == capacity;}
    bool is_empty() {return remaining_volume == 0U;}
    bool is_running_on_fumes()
    {
        auto ratio = static_cast<float>(remaining_volume) / static_cast<float>(capacity);
        return (ratio <= 0.02);
    }
    uint32_t fill_up()
    {
        auto added_volume = capacity - remaining_volume;
        remaining_volume = capacity;
        return added_volume;
    }


    uint32_t get_capacity() const {return capacity;}
    uint32_t get_remaining_volume() const {return remaining_volume;}
    Fuel get_fuel_type() const {return fuel_type;}
    void attach_sensor(electrical::AbstractSensor& _fuel_gauge)
    {
        fuel_gauge = &_fuel_gauge;
    }

private:
    electrical::AbstractSensor * fuel_gauge = nullptr;
    uint32_t capacity = 45U;
    uint32_t remaining_volume;
    Fuel fuel_type = Fuel::gasoline;
};


}

#endif /* _FUEL_TANK_HEADER_ */