#include <assert.h>
#include "maths.h"


void test_linear_map(void)
{
    map_ranges_t input_range = {.start = 10 , .end = 150 };
    map_ranges_t output_range = {.start = 250 , .end = 836 };

    uint16_t test_value = 13U;

    uint16_t mapped_value = linear_remap(test_value, &input_range, &output_range);
    assert(mapped_value == 261);
}



int main(int argc, char** argv)
{
    (void) argc;
    (void) argv;

    test_linear_map();

    return 0;
}