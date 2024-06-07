#include <stdint.h>


#define WIDTH 5U
#define HEIGHT 8U

int main()
{
    uint8_t array [WIDTH][HEIGHT] = {0};

    for(uint8_t i = 0 ; i < WIDTH ; i++)
    {
        for(uint8_t j = 0 ; j < HEIGHT ; j++)
        {
            // [line][column]
            array[i][j] = (uint8_t)(i+1)*(j+1);
        }
    }

    return 0;
}