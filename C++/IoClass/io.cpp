#include "io.h"
#include "mock_register.h"
#include "stm32f051xx_io_mapping.h"

//using namespace ::peripheral;

namespace peripheral
{
io::config::config( io::config::State _st,
                    io::config::Speed _sp,
                    io::config::Topology _t,
                    io::config::Mode _m) :
                        state(_st),
                        speed(_sp),
                        topology(_t),
                        mode(_m)
{}

/* Identity */

io::identity::identity(const uint32_t * const _port, uint32_t _pin) : port((uint32_t *) _port), pin(_pin)
{}
io::identity& io::identity::operator=(const identity& other)
{
    port = other.port;
    pin = other.pin;
}

/* Config */
io::config::config() :
    state(io::config::State::low),
    speed(io::config::Speed::high),
    topology(io::config::Topology::tristate),
    mode(io::config::Mode::input) {}



io::config::Mode io::get_mode()
{
    uint32_t index = (MOCK::get_portindex(id.port));
    return  ::MOCK::ioregisters[index].mode;
}

/* Io */
io::io(const io::identity& _id) : id(_id){}

void io::set_mode(io::config::Mode m)
{
    uint32_t index = (MOCK::get_portindex(id.port));
    ::MOCK::ioregisters[index].mode = m;
}

io::config::Topology io::get_topology()
{
    uint32_t index = (MOCK::get_portindex(id.port));
    return  ::MOCK::ioregisters[index].topology;
}

void io::set_topology(io::config::Topology t)
{
    uint32_t index = (MOCK::get_portindex(id.port));
    ::MOCK::ioregisters[index].topology = t;
}

io::config::Speed io::get_speed()
{
    uint32_t index = (MOCK::get_portindex(id.port));
    return  ::MOCK::ioregisters[index].speed;
}

void io::set_speed(io::config::Speed s)
{
    uint32_t index = (MOCK::get_portindex(id.port));
    ::MOCK::ioregisters[index].speed = s;
}

io::config::State io::read()
{
    uint32_t index = (MOCK::get_portindex(id.port));
    return  ::MOCK::ioregisters[index].state;
}

void io::write(io::config::State s)
{
    uint32_t index = (MOCK::get_portindex(id.port));
    ::MOCK::ioregisters[index].state = s;
}

void io::setup(const io::config& _config)
{
    set_topology(_config.topology);
    set_mode(_config.mode);
    set_speed(_config.speed);
    write(_config.state);
}

void io::set_identity(const io::identity& _id)
{
    id = _id;
}

io::identity io::get_identity()
{
    return id;
}

}