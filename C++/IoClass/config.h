#ifndef _HAL_MAPPING_HEADER_
#define _HAL_MAPPING_HEADER_

#include "io.h"

namespace peripheral
{

extern const io::identity coil_drive_id;
extern const io::identity fan_drive_1_id;
extern const io::identity fan_drive_2_id;

extern const io::config coil_drive_config;
extern const io::config fan_drive_1_config;
extern const io::config fan_drive_2_config;

}

#endif /* _HAL_MAPPING_HEADER_ */