#ifndef _USER_IOS_HEADER_
#define _USER_IOS_HEADER_

#include "io.h"
#include "stm32f051xx_io_mapping.h"

namespace userIo
{
static peripheral::io coil_drive(peripheral::io::identity(
                peripheral::stm32f051xx::GIO_PORTA, 2U));

static peripheral::io fan_drive_1(peripheral::io::identity(
                peripheral::stm32f051xx::GIO_PORTA, 3U));

static peripheral::io fan_drive_2(peripheral::io::identity(
                peripheral::stm32f051xx::GIO_PORTA, 4U));

static peripheral::io rpm_probe(peripheral::io::identity(
                peripheral::stm32f051xx::GIO_PORTA, 5U));
}
#endif /* _USER_IOS_HEADER_ */