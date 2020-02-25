#include "io.h"
#include "config.h"
#include "stm32f051xx_io_mapping.h"

namespace peripheral
{
// Where to find those GPIOs
const io::identity coil_drive_id(stm32f051xx::GIO_PORTA,0U);

const io::identity fan_drive_1_id(stm32f051xx::GIO_PORTB,2U);
const io::config fan_drive_1_config(io::config::State::low,
                                   io::config::Speed::low,
                                   io::config::Topology::push_pull,
                                   io::config::Mode::output );

const io::identity fan_drive_2_id(stm32f051xx::GIO_PORTC,7U);
const io::config fan_drive_2_config(io::config::State::low,
                                   io::config::Speed::low,
                                   io::config::Topology::push_pull,
                                   io::config::Mode::output );

}