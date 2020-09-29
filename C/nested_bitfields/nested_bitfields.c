
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
typedef struct
{
        struct
        {
            bool flag1 : 1;
            bool flag2 : 1;
        } bitfield1;
        struct
        {
            bool flag1 : 1;
            bool flag2 : 1;
        } bitfield2 ;
}  nested_bitfield_struct_t;

int main(void)
{
    nested_bitfield_struct_t st;
    st.bitfield1.flag1 = 1;
    st.bitfield1.flag2 = 0;
    printf("size of nested_bitfield_struct_t = %d\n", sizeof(nested_bitfield_struct_t));
    return 0;
}
