#include <stdio.h>

typedef struct 
{
    int a;
    struct 
    {
        int b;
        int a;
    }B;
} A;

void print_A( A * const a)
{
    printf("A = {\n");
    printf("    a = %d\n",a->a);
    printf("       B = {\n");
    printf("             a = %d\n",a->B.a);
    printf("             b = %d\n",a->B.b);
    printf("           }\n");
    printf("    }\n");
}

int main()
{
    A a = 
    {
        .a = 2,
        .B = 
        {
            .a = 5,
            .b = 8
        }
    };
    print_A(&a);

    return 0;
}