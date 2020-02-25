#include <iostream>
#include "io.h"
#include "config.h"
#include "stm32f051xx_io_mapping.h"
#include "debug_utils.hpp"
#include "setup.h"
#include "userIOs.hpp"
#include "mock_register.h"

int main(int argc, char** argv)
{
    (void) argc;
    (void) argv;

    setup_ios();

    std::cout << "Printing coil drive io structure and related MOCK object" << std::endl;
    debug::print_io_struct(userIo::coil_drive);
    std::cout << "Mock object :\n";
    debug::print_config_struct(MOCK::get_mock_io_config(peripheral::stm32f051xx::GIO_PORTA));

    std::cout << "\nPrinting fan drive 1 io structure and related MOCK object" << std::endl;
    debug::print_io_struct(userIo::fan_drive_1);
    std::cout << "Mock object :\n";
    debug::print_config_struct(MOCK::get_mock_io_config(peripheral::stm32f051xx::GIO_PORTA));

    std::cout << "\nPrinting fan drive 2 io structure and related MOCK object" << std::endl;
    debug::print_io_struct(userIo::fan_drive_2);
    std::cout << "Mock object :\n";
    debug::print_config_struct(MOCK::get_mock_io_config(peripheral::stm32f051xx::GIO_PORTA));

    return 0;
}