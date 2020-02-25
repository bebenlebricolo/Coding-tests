#include "io.h"
#include "mock_register.h"
#include "stm32f051xx_io_mapping.h"

namespace MOCK
{

::peripheral::io::config ioregisters[4] =
{
    {::peripheral::io::config()},
    {::peripheral::io::config()},
    {::peripheral::io::config()},
    {::peripheral::io::config()},
};

uint32_t get_portindex(const uint32_t * const port)
{
    uint64_t address = (uint64_t) port;
    if( address == (uint64_t) ::peripheral::stm32f051xx::GIO_PORTA)
        return 0U;
    if(address == (uint64_t) ::peripheral::stm32f051xx::GIO_PORTB)
        return 1U;
    if(address == (uint64_t) ::peripheral::stm32f051xx::GIO_PORTC)
        return 2U;
    if(address == (uint64_t) ::peripheral::stm32f051xx::GIO_PORTD)
        return 3U;
    return 5;
}

const peripheral::io::config& get_mock_io_config(const uint32_t * const port)
{
    uint32_t index = get_portindex(port);
    return ioregisters[index];
}


}