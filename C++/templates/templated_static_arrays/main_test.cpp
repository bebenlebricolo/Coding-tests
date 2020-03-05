template <typename T, unsigned int Capacity>
struct StaticArray
{
    template <unsigned int InputCount>
    constexpr StaticArray(T const (&data)[InputCount])
    {
        static_assert(InputCount <= Capacity, "Out of range");
        // magic ^^
    }
};

int main()
{
    unsigned int array[] = {1,2,3};
    unsigned int array2[] = {1,2,3,4,5,6};
    constexpr auto toto = StaticArray<unsigned int, 3>(array);
    constexpr auto tata = StaticArray<unsigned int, 3>(array2);
    constexpr StaticArray<unsigned int, 3> titi(array);
}