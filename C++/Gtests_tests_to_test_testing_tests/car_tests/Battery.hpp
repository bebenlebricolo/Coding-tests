#ifndef _BATTERY_CLASS_HEADER_
#define _BATTERY_CLASS_HEADER_

#include <memory>
#include <cstdint>
#include "AbstractSensor.hpp"

namespace electrical
{

enum class BatteryAction
{
    charging,
    depleting,
    idle
};

class Battery
{
public:
    Battery(uint32_t _remaining_capacity = 80000U,
            float _actual_voltage = 11.73) :
                remaining_capacity(_remaining_capacity),
                actual_voltage(_actual_voltage)
    {}
    Battery(AbstractSensor& _current_sensor,
            uint32_t _remaining_capacity = 80000U,
            float _actual_voltage = 11.73) :
                current_sensor(&_current_sensor)
    {}

    BatteryAction get_battery_action() const
    {
        auto current_flow = current_sensor->read();
        if (current_flow < 0)
            return BatteryAction::depleting;
        else if (current_flow > leaking_charge_voltage_threshold )
            return BatteryAction::charging;
        else
            return BatteryAction::idle;
    }
    bool is_charged() const
    {
        if ((get_battery_action() == BatteryAction::idle)
        &&  ((actual_voltage / nominal_voltage) >= charged_threshold))
        {
            return true;
        }
        return false;
    }
    uint32_t get_remaining_capacity() const {return remaining_capacity;}
    float get_charge_ratio() const {return static_cast<float>(actual_voltage) / static_cast<float>(nominal_voltage);}
    void attach_sensor(AbstractSensor& sensor)
    {
        current_sensor = &sensor;
    }

    static const uint32_t get_max_capacity() {return maximum_capacity;}
    static const float get_max_voltage() {return element_max_voltage * element_count;}

private:
    // Modelises the internals of a lead-based battery
    static const float element_nominal_voltage;
    static const float element_max_voltage;
    static const float element_min_voltage;
    static const uint8_t element_count;
    static const uint32_t maximum_capacity;
    static const float charged_threshold;
    static const int32_t leaking_charge_voltage_threshold;

    AbstractSensor * current_sensor;
    uint32_t remaining_capacity;
    float nominal_voltage = element_nominal_voltage * element_count;
    float actual_voltage;
};

const uint32_t Battery::maximum_capacity = 90'000U;
const float Battery::element_nominal_voltage = 2.1;
const float Battery::element_max_voltage = 2.2;
const float Battery::element_min_voltage = 1.9;
const uint8_t Battery::element_count = 6U;
const float Battery::charged_threshold = 0.95;
const int32_t Battery::leaking_charge_voltage_threshold = 500;



}



#endif /* _BATTERY_CLASS_HEADER_ */