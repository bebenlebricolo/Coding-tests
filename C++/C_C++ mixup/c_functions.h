#ifndef _C_FUNCTIONS_HEADER_
#define _C_FUNCTIONS_HEADER_


#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdlib.h>
#include "c_interface.h"

int print_stuff_to_screen(char * msg, unsigned int size);
void use_classes_callback(class_enum_t c);

#ifdef __cplusplus
}
#endif

#endif /* _C_FUNCTIONS_HEADER_ */