#ifndef _MOCK_FUEL_TANK_CLASS_HEADER_
#define _MOCK_FUEL_TANK_CLASS_HEADER_

#include "FuelTank.hpp"
#include "AbstractSensor.hpp"

namespace mechanical
{

class MockFuelTank : public FuelTank
{
public:
    MockFuelTank() : FuelTank() {}
    MockFuelTank(uint32_t _capacity, uint32_t _remaining_volume, Fuel _fuel_type):
        FuelTank(_capacity, _remaining_volume, _fuel_type) {}

    bool is_full() {return FuelTank::is_full();}
    bool is_empty() {return FuelTank::is_empty();}
    bool is_running_on_fumes() {return FuelTank::is_running_on_fumes();}
    uint32_t fill_up() {return FuelTank::fill_up();}

    uint32_t get_remaining_volume() const {return FuelTank::get_remaining_volume();}
    uint32_t get_capacity() const {return FuelTank::get_capacity();}
    Fuel get_fuel_type() const {return FuelTank::get_fuel_type();}
    void attach_sensor(electrical::AbstractSensor& sensor) {FuelTank::attach_sensor(sensor);}
};

}
#endif /* _MOCK_FUEL_TANK_CLASS_HEADER_ */