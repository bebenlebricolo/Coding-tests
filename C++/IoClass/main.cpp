#include <iostream>
#include "io.h"
#include "config.h"
#include "stm32f051xx_io_mapping.h"
#include "debug_utils.hpp"



int main(int argc, char** argv)
{
    (void) argc;
    (void) argv;

    ::peripheral::io coil_drive_io(peripheral::coil_drive_id);
    ::peripheral::io fan_drive_1_io(peripheral::fan_drive_1_id);
    ::peripheral::io fan_drive_2_io(peripheral::fan_drive_2_id);

    coil_drive_io.setup(peripheral::coil_drive_config);
    fan_drive_1_io.setup(peripheral::fan_drive_1_config);
    fan_drive_2_io.setup(peripheral::fan_drive_2_config);

    debug::print_io_struct(coil_drive_io);
    debug::print_io_struct(fan_drive_1_io);
    debug::print_io_struct(fan_drive_2_io);


    return 0;
}