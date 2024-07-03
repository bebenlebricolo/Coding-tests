#include <stdint.h>
#include <stdio.h>

#define WIDTH 5U
#define HEIGHT 8U


void print_array(uint8_t* array, const uint8_t width, const uint8_t height)
{
    for(uint8_t j = 0; j < height ; j++)
    {
        for(uint8_t i = 0 ; i < width ; i++)
        {
            printf("%u ", array[i + j * width]);
        }
        printf("\n");
    }
    printf("\n");
}


void print_array_sequential(uint8_t * array, uint8_t length)
{
    for(uint8_t i = 0 ; i < length ; i++)
    {
        printf("%u ", array[i]);
    }
    printf("\n");
}

void print_array_typed(uint8_t array[WIDTH][HEIGHT])
{
    for(uint8_t j = 0; j < HEIGHT ; j++)
    {
        for(uint8_t i = 0 ; i < WIDTH ; i++)
        {
            printf("%u ", array[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int main()
{
    printf("This little program illustrates the differences in memory layout between Nth dimensions arrays and single continuous array\n");

    //             X       Y
    uint8_t array [WIDTH][HEIGHT] = {0};
    uint8_t sum = 0;
    for(uint8_t j = 0 ; j < HEIGHT ; j++)
    {
        for(uint8_t i = 0 ; i < WIDTH ; i++)
        {
            // [row][column]
            array[i][j] = sum;
            sum++;
        }
    }

    printf("Printing array using index arithmetic with array[i + j * width]\n");
    print_array((uint8_t*) array, WIDTH, HEIGHT);

    printf("Printing typed array (with array[WIDTH][HEIGHT] signature)\n");
    print_array_typed(array);

    printf("Printing continuous (as if array was single dimension : array[i])\n");
    print_array_sequential((uint8_t*) array, WIDTH * HEIGHT);

    printf("Note : the only method that recomposes the array as it should be displayed (5 columns, 8 rows) is the \"typed array\" one\n");

    return 0;
}
