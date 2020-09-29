#include "module.h"
#include "common_header.h"


int main(void)
{
    module_init();
    module_do_something();  
    external_function();
    return 0;
}
