#ifndef _IO_OBJECT_HEADER_
#define _IO_OBJECT_HEADER_

#include <stdint.h>

namespace peripheral
{

class io
{
public:
    struct config
    {
        // Determines io electrical state in both write or read mode
        enum class State
        {
            low = 0,
            high = 1
        };

        // Describes io port speed
        enum class Speed
        {
            low,
            medium,
            high
        };

        // Describes which electrical characteristics needs to be applied to an io port
        enum class Topology
        {
            push_pull,
            open_drain,
            tristate
        };

        // Aka "Direction"
        enum class Mode
        {
            output,
            input
        };

        config();
        config(State _st, Speed _sp, Topology _t, Mode _m);

        State state;
        Speed speed;
        Topology topology;
        Mode mode;
    };

    struct identity
    {
        identity(const uint32_t * const _port, uint32_t _pin);
        identity(const identity& other) = default;
        identity& operator=(const identity& other);
        uint32_t * port;
        uint32_t   pin;
    };

    io()=delete;
    io(const io& other) = default;
    io(const identity& _id);

    void set_identity(const identity& _id);
    identity get_identity();

    config::State read();
    void write(config::State s);

    config::State get_state();
    void set_state(config::State s);

    void set_mode(config::Mode m);
    config::Mode get_mode();

    void set_topology(config::Topology t);
    config::Topology get_topology();

    void set_speed(config::Speed s);
    config::Speed get_speed();

    void setup(const config& _config);

    /* Add necessary code to handle ISRs */

    identity id;
};

} /* namespace peripheral */

#endif /* _IO_OBJECT_HEADER_ */