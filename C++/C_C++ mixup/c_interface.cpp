#include "c_interface.h"
#include "class_collection.hpp"

void run_callback(class_enum_t c)
{
    if((unsigned int) c < CLASS_COUNT)
    {
        class_collection[c].run_callback();
    }
}