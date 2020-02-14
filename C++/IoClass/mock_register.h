#ifndef _MOCK_REGISTER_HEADER_
#define _MOCK_REGISTER_HEADER_

#include "io.h"
#include "stm32f051xx_io_mapping.h"

namespace MOCK
{
uint32_t get_portindex(const uint32_t * const port);
extern ::peripheral::io::config ioregisters[4];
}

#endif