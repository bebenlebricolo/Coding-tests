#include "setup.h"
#include "io.h"
#include "config.h"
#include "userIOs.hpp"

void setup_ios()
{
   {
    peripheral::io::config _config( peripheral::io::config::State::low,
                                    peripheral::io::config::Speed::high,
                                    peripheral::io::config::Topology::push_pull,
                                    peripheral::io::config::Mode::output );
    userIo::coil_drive.setup(_config);
   }

   {
    peripheral::io::config _config( peripheral::io::config::State::low,
                                    peripheral::io::config::Speed::low,
                                    peripheral::io::config::Topology::push_pull,
                                    peripheral::io::config::Mode::output );
    userIo::fan_drive_1.setup(_config);
   }

   {
    peripheral::io::config _config( peripheral::io::config::State::high,
                                    peripheral::io::config::Speed::low,
                                    peripheral::io::config::Topology::push_pull,
                                    peripheral::io::config::Mode::output );
    userIo::fan_drive_2.setup(_config);
   }

}