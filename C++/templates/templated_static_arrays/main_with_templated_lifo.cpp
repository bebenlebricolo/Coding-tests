#include <cstdint>
#include "fixed_size_lifo.hpp"

struct SuperStruct
{
    SuperStruct();
    template<uint32_t S1, uint32_t S2>
    SuperStruct(uint16_t (&a1)[S1],uint16_t (&a2)[S2]) :
        array1(a1),
        array2(a2)
    {}
    FixedSizedLifo<uint16_t,2> array1;
    FixedSizedLifo<uint16_t,2> array2;
    void print() const
    {
        array1.print();
        array2.print();
    }

};

int main(int argc, char** argv)
{
    (void) argc;
    (void) argv;


    uint16_t array_a[] = {4,25};
    uint16_t array_b[] = {3,4};

    FixedSizedLifo<uint16_t, 3> toto(array_a);
    // Copy constructor
    FixedSizedLifo<uint16_t, 3> tutu(toto);
    SuperStruct tata(array_a,array_b);

    toto.print();
    toto[2] = 5;
    toto[0] = 6;
    tata.print();

    FixedSizedLifo<uint16_t, 4> persistent_array;
    {
        uint16_t array_ctemp[] = {58,64,985};
        persistent_array.set_array(array_ctemp);
        persistent_array.push(33);
    }
    persistent_array.print();
    persistent_array[0] = 41;
    persistent_array[1] = 12;
    persistent_array[2] = 28;
    persistent_array.print();

    return 0;
}