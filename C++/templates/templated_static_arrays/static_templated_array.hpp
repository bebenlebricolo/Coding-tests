#include <memory>
#include <iostream>
#include <cstdint>
#include <initializer_list>

template <typename T , std::size_t Capacity>
struct StaticArray
{
    StaticArray() : array(){}
    template <std::size_t InputCount>
    constexpr StaticArray(const T (&data)[InputCount]) : array()
    {
        static_assert( InputCount <= Capacity);
        for (auto elt : data)
        {
            push(elt);
        }
    }

    StaticArray(StaticArray& other)
    {
        for( auto elt : other.array)
        {
            push(elt);
        }
    }
    constexpr void push(T& val)
    {
        array[elt_count] = val;
        elt_count++;
    }
    constexpr void print() const
    {
        for (auto elt : array)
        {
            std::cout<< elt << std::endl;
        }
    }

private:
    T array[Capacity];
    uint32_t elt_count = 0;
};