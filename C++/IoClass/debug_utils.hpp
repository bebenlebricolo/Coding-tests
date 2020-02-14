#ifndef _DEBUG_UTILS_HEADER_
#define _DEBUG_UTILS_HEADER_

#include <iostream>
#include <string>
#include "io.h"

namespace debug
{
using namespace std;
using namespace peripheral;
string State_tostring(io::config::State s)
{
    switch (s)
    {
        case io::config::State::high:
            return "high";
        default:
            return "low";
    }
}

string Speed_tostring(io::config::Speed s)
{
    switch (s)
    {
        case io::config::Speed::high:
            return "high";
        case io::config::Speed::medium:
            return "medium";
        default:
            return "low";
    }
}

string Topology_tostring(io::config::Topology t)
{
    switch (t)
    {
        case io::config::Topology::push_pull:
            return "push_pull";
        case io::config::Topology::open_drain:
            return "open_drain";
        default:
            return "tristate";
    }
}


string Mode_tostring(io::config::Mode m)
{
    switch (m)
    {
        case io::config::Mode::output:
            return "output";
        default:
            return "input";
    }
}

void print_config_struct(const ::peripheral::io::config& config)
{
    cout << "config : \n"
         << "\tstate = " << State_tostring(config.state) << endl
         << "\tspeed = " << Speed_tostring(config.speed) << endl
         << "\ttopology = " << Topology_tostring(config.topology) << endl
         << "\tmode = " << Mode_tostring(config.mode) << endl;

}

void print_identity_struct(const ::peripheral::io::identity& id)
{
    cout << "identity : \n"
         << "\tport = " << id.port << endl
         << "\tpin = " << id.pin << endl << endl;
}

void print_io_struct(const ::peripheral::io& obj)
{
    cout << "io struct : " << endl;
    print_identity_struct(obj.id);
}

}


#endif
