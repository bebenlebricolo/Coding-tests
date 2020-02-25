#include <iostream>
#include <string>


class IOStuff
{
    enum
    {
        UNKNOWN,
        FILE_NOT_FOUND,
        WRONG_PERMISSIONS
    };

};
static const char* convertion_table[3] =
{
    [0] = {"UNKNOWN"},
    [1] = {"FILE_NOT_FOUND"},
    [2] = {"WRONG_PERMISSIONS"}
};