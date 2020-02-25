#ifndef _MOCK_ENGINE_CLASS_HEADER_
#define _MOCK_ENGINE_CLASS_HEADER_

#include "Engine.hpp"
#include "FuelTank.hpp"

namespace mechanical
{

class MockEngine : public Engine
{
public:
    MockEngine(): Engine() {}
    MockEngine(uint8_t _cylinders, uint32_t _power, uint32_t _volume, float _specific_consumption):
        Engine(_cylinders,_power,_volume,_specific_consumption)
    {}
    EngineState start() {return Engine::start();}
    EngineState get_state() const {return Engine::get_state();}
    uint8_t get_cylinders() const {return Engine::get_cylinders();}
    void set_fuel_tank(mechanical::FuelTank& _fuel_tank) { Engine::set_fuel_tank(_fuel_tank);}
    void set_battery(electrical::Battery& _battery) {Engine::set_battery(_battery);}
};
}
#endif /* _MOCK_ENGINE_CLASS_HEADER_ */