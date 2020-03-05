#include <cstdint>
#include "static_templated_array.hpp"

struct SuperStruct
{
    SuperStruct();
    template<uint32_t S1, uint32_t S2>
    constexpr SuperStruct(const uint16_t (&a1)[S1],const uint16_t (&a2)[S2]) :
        array1(a1),
        array2(a2)
    {}
    StaticArray<uint16_t,2> array1;
    StaticArray<uint16_t,2> array2;
    constexpr void print() const
    {
        array1.print();
        array2.print();
    }

};

int main(int argc, char** argv)
{
    (void) argc;
    (void) argv;

    constexpr uint16_t array_a[] = {4,25};
    constexpr uint16_t array_b[] = {3,4};

    constexpr StaticArray<uint16_t, 3> toto(array_a);
    // Copy constructor
    constexpr StaticArray<uint16_t, 3> tutu(toto);
    constexpr SuperStruct tata(array_a,array_b);

    toto.print();
    tata.print();

    return 0;
}