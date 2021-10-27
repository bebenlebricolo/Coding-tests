#include "maths.h"

uint16_t range_span(map_ranges_t const * const range)
{
    uint16_t out;
    if (range->start < range->end)
    {
        out = range->end - range->start;
    }
    else
    {
        out = range->start - range->end;
    }
    return out;
}


uint16_t linear_remap(uint16_t input_data, map_ranges_t const * const input_range, map_ranges_t const * const output_range )
{
    uint16_t offset_val = input_data - input_range->start;
    uint16_t out = (offset_val * 100U) / range_span(input_range);
    out = (out * range_span(output_range)) / 100 + output_range->start;
    return out;
}
