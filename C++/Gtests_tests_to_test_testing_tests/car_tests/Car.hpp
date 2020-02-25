#ifndef _CAR_CLASS_HEADER_
#define _CAR_CLASS_HEADER_

#include "Engine.hpp"
#include "FuelTank.hpp"
#include "Battery.hpp"

enum class CarState
{
    ready_to_go,
    stopped
};


class Car
{
public :
    Car() = delete;
    Car(mechanical::Engine& _engine,
        mechanical::FuelTank &_fuel_tank,
        electrical::Battery &_battery) :
            engine(_engine),
            fuel_tank(_fuel_tank),
            battery(_battery)
    {}
    CarState setup()
    {
        if (engine.start() == mechanical::EngineState::started)
        {
            state = CarState::ready_to_go;
        }
        else
            state = CarState::stopped;
        return state;
    }
    bool can_drive() const
    {
        if (state == CarState::ready_to_go)
        {
            return (engine.get_state() == mechanical::EngineState::started);
        }
        else
            return false;
    }
    CarState get_state() {return state;}


private:
    mechanical::Engine &engine;
    mechanical::FuelTank &fuel_tank;
    electrical::Battery& battery;
    CarState state = CarState::stopped;
};



#endif