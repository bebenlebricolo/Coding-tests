#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// 'degC', 8x15px
const uint8_t sm_5x15_degC [] = {
    0x70, 0xd8, 0x88, 0xd8, 0x70, 0x00, 0x78, 0xf8, 0xe0, 0xc0, 0xc0, 0xc0, 0xe0, 0xf8, 0x78
};


void print_help(void)
{
    printf("Usage : printer x y\n");
    printf("Where x : x offset (positive) in pixels\n");
    printf("      y : y offset (positive) in pixels\n");
}

// Prints out a "°C" character
// Thanks to this little program, we can find out that the above character is written in memory in a left-right and top-down fashion
//  (0,0) ------> (7,0)
//    |
//    |
//    |
//    |
//  (0,14)

int main(int argc, char** argv)
{
    int x_offset = 0;
    int y_offset = 0;
    if(argc == 3U)
    {
        x_offset = atoi(argv[1U]);
        y_offset = atoi(argv[2U]);

        if(x_offset < 0  || y_offset < 0)
        {
            printf("Error : x and y offset shall be positive only.");
            print_help();
            return 1U;
        }
    }
    else
    {
        printf("Error : Not given enough arguments.");
        print_help();
        return 1U;
    }

    // First consume y offset
    if(y_offset != 0)
    {
        for(uint8_t i = 0 ; i < y_offset; i++)
        {
            printf("\n");
        }
    }

    for (uint8_t i = 0; i < 15U; i++)       // iterates over the lines
    {
        uint8_t data = sm_5x15_degC[i];

        // First consume x offset
        if(x_offset != 0)
        {
            for(uint8_t i = 0 ; i < x_offset ; i++)
            {
                printf(" ");
            }
        }

        for( uint8_t j = 0 ; j < 8U ; j++)  // iterates over the single bits (columns)
        {
            uint8_t bit = (data & (1 << 7));
            data <<= 1;

            if(bit)
            {
                printf("#");
            }
            else
            {
                printf(" ");
            }
        }
        printf("\n");
    }


    return 0;
}

