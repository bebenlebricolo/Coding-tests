#include "module.h"
#include <stdio.h>

#include "common_header.h"

bool module_init(void)
{
    printf("Module initialised!\n");
    return true;
}

void module_do_something(void)
{
    printf("Hello World\n");
}

void external_function(void)
{
    printf("Called from a module declared somewhere else!\n");
}
