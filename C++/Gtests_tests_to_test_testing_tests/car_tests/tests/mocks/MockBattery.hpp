#ifndef _MOCK_BATTERY_CLASS_HEADER_
#define _MOCK_BATTERY_CLASS_HEADER_

#include "MockCurrentSensor.hpp"
#include "Battery.hpp"

namespace electrical
{

class MockBattery : public Battery
{
public:
    MockBattery(uint32_t _remaining_capacity, float _actual_voltage) :
            Battery(_remaining_capacity, _actual_voltage)
    {}
    MockBattery(MockCurrentSensor &_sensor, uint32_t _remaining_capacity, float _actual_voltage) :
            Battery(_sensor, _remaining_capacity, _actual_voltage)
    {}

    // points to base class if no overriding is needed
    BatteryAction get_battery_action() const {return Battery::get_battery_action();}
    bool is_charged() const {return Battery::is_charged();}

    uint32_t get_remaining_capacity() const {return Battery::get_remaining_capacity();}
    float get_charge_ratio() const {return Battery::get_charge_ratio();}
    void attach_sensor(AbstractSensor& sensor)
    {
        Battery::attach_sensor(sensor);
    }

};

}

#endif /* _MOCK_BATTERY_CLASS_HEADER_ */
