#include <cstdint>
#include <initializer_list>

template <typename T , uint32_t SizeMax>
struct StaticArray
{
    StaticArray(){}
    StaticArray(std::initializer_list<T> l)
    {
        for (auto elt : l)
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
    void push(T& val)
    {
        array[elt_count] = val;
        elt_count++;
    }
private:
    T array[SizeMax];
    uint32_t elt_count = 0;
};


int main(int argc, char** argv)
{
    (void) argc;
    (void) argv;

    StaticArray<uint16_t,3> toto{1,2,3};

    return 0;
}