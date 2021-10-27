#ifndef MATHS_HEADER
#define MATHS_HEADER

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>

typedef struct
{
    uint16_t start;
    uint16_t end;
} map_ranges_t;

/**
 * @brief calculates the range's span
 * @param range : evaluated range
 * @return span
 */
uint16_t range_span(map_ranges_t const * const range);

/**
 * @brief remaps an input value within the input range into the output range
 * @param input_data    : input data value in input range (has to be included in the range)
 * @param input_range   : input data range
 * @param output_range  : output data range
 * @return remapped value
*/
uint16_t linear_remap(uint16_t input_data, map_ranges_t const * const input_range, map_ranges_t const * const output_range );


#ifdef __cplusplus
}
#endif

#endif /* MATHS_HEADER */