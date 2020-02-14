#include <stdio.h>

/* Defining io properties for system */
typedef enum {
    UNKNOWN,
    FILE_NOT_FOUND,
    WRONG_PERMISSIONS
} IoStuff;

#define addKey(enum) [enum]=#enum

static const char * convert_table[] =
{
    addKey(UNKNOWN),
    addKey(FILE_NOT_FOUND),
    addKey(WRONG_PERMISSIONS)
};

const char* convert_enum(IoStuff e)
{
    return convert_table[e];
}


int main(int argc, char **argv)
{
    printf("Unknown enum = : \"%s\"\n", convert_enum(UNKNOWN));
    printf("file not found enum = : \"%s\"\n", convert_enum(FILE_NOT_FOUND));
    printf("wrong permissions enum = : \"%s\"\n", convert_enum(WRONG_PERMISSIONS));
    return 0;
}