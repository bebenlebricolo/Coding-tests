#ifndef _FIXED_SIZE_LIFO_CLASS_HEADER_
#define _FIXED_SIZE_LIFO_CLASS_HEADER_

#include <memory>
#include <iostream>
#include <cstdint>
#include <initializer_list>

template <typename T , std::size_t Capacity>
class FixedSizedLifo
{
public:
    FixedSizedLifo():array(){};
    template <std::size_t InputCount>
    FixedSizedLifo(T (&data)[InputCount]) : array(), elt_count(0)
    {
        static_assert( InputCount <= Capacity);
        for (auto elt : data)
        {
            push(elt);
        }
    }

    FixedSizedLifo(const FixedSizedLifo& other) : FixedSizedLifo()
    {
        for(auto elt : other.array)
        {
            push(elt);
        }
    }

    void clear()
    {
        for(uint32_t i = 0; i < Capacity ; i++)
        {
            array[i] = 0;
        }
        elt_count = 0;
    }

    template <std::size_t InputCount>
    void set_array(T (&data)[InputCount])
    {
        copy_array(data);
    }

    void push(T& val)
    {
        if (elt_count < Capacity)
        {
            array[elt_count] = val;
            elt_count++;
        }
    }
    void push(const T&& val)
    {
        if (elt_count < Capacity)
        {
            array[elt_count] = val;
            elt_count++;
        }
    }

    void print() const
    {
        for (auto elt : array)
        {
            std::cout<< elt << std::endl;
        }
    }

    T& operator[](uint32_t index)
    {
        if (index <= (elt_count - 1))
        {
            return array[index];
        }
        return array[0];
    }

private:
    T array[Capacity];
    uint32_t elt_count = 0;

    template <std::size_t InputCount>
    void copy_array(T (&data)[InputCount])
    {
        static_assert( InputCount <= Capacity);
        clear();
        for (auto elt : data)
        {
            push(elt);
        }
    }
};

#endif /* _FIXED_SIZE_LIFO_CLASS_HEADER_ */