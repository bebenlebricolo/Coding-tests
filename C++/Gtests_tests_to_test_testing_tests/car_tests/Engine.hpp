#ifndef _ENGINE_CLASS_HEADER_
#define _ENGINE_CLASS_HEADER_

#include <cstdint>
#include "FuelTank.hpp"
#include "Battery.hpp"

namespace mechanical
{

enum class EngineState
{
    started,
    stalled
};

class Engine
{
public:
    Engine(){}
    Engine(uint8_t _cylinders, uint32_t _power, uint32_t _volume, float _specific_consumption):
        cylinders(_cylinders),
        power(_power),
        volume(_volume),
        specific_consumption(_specific_consumption)
    {}

    EngineState start()
    {
        // Lot of procedures to make the engine start ...
        if (fuel_tank == nullptr || battery == nullptr)
        {
            state = EngineState::stalled;
            return state;
        }

        if (!fuel_tank->is_empty() && (battery->get_charge_ratio() > 0.3))
        {
            state = EngineState::started;
        }
        else
        {
            state = EngineState::stalled;
        }
        return state;
    }
    EngineState get_state() const {return state;}
    EngineState stop()
    {
        state = EngineState::stalled;
        return state;
    }

    uint8_t get_cylinders() const {return cylinders;}
    void set_fuel_tank(FuelTank& _fuel_tank) {fuel_tank = &_fuel_tank;}
    void set_battery(electrical::Battery& _battery) {battery = &_battery;}

protected:
    EngineState state = EngineState::stalled;
    FuelTank * fuel_tank = nullptr;
    electrical::Battery * battery = nullptr;
    uint8_t cylinders = 4U;
    uint32_t power = 55U;
    uint32_t volume = 900U;
    float specific_consumption = 6.5;
};




}

#endif /* _ENGINE_CLASS_HEADER_ */