#ifndef _C_INTERFACE_HEADER_
#define _C_INTERFACE_HEADER_

#ifdef __cplusplus
extern "C" {
#endif

typedef enum
{
    CLASS_1,
    CLASS_2,
    CLASS_3,
    CLASS_COUNT
} class_enum_t;

void run_callback(class_enum_t c);

#ifdef __cplusplus
}
#endif

#endif /* _C_INTERFACE_HEADER_ */
