#include <stdio.h>
#include <stddef.h>
#include <stdbool.h>
#include "c_functions.h"
#include "c_interface.h"

int print_stuff_to_screen(char * msg, unsigned int size)
{
    int ret = -1;
    if (NULL != msg && 0 != size)
    {
        (void) size;
        ret = (printf(msg) == 0) ? 0 : -1;
    }
    return ret;
}

void use_classes_callback(class_enum_t c)
{
    run_callback(c);
}

