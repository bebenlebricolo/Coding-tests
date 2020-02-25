#include <stdio.h>

// Declaration
unsigned int suite_geometrique(unsigned int a);

// Definition
unsigned int suite_geometrique(unsigned int a)
{
    unsigned int result = 0;
    for (unsigned int i = 0 ; i < 123 ; i++)
    {
        result = result + a * i ;
    }
    return result;
}


int main (int argc, char ** argv)
{
    for (int i = 0; i < argc ; i++)
    {
        printf("Arg[%d] : %s \n",i,argv[i]);
    }


    printf("La suite géométrique de 0 à 123 pour a = %u vaut : %u\n",3,suite_geometrique(3));

    return 0;
}