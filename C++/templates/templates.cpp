#include "pseudo_vector.hpp"

using namespace pseudo_vector_test;

int main(const int argc, const char * const * argv)
{
    generic_list<int> intlist;

#ifdef EXTENDED_TYPES
    generic_list<float> floatlist;
    generic_list<uint8_t> octetlist;
#endif

    try {
        intlist.push(33);
        intlist.push(58);
        for (uint32_t i = 0 ; i < 20 ; i++) {
            intlist.push(i*i+2);
        }
        intlist.print();
        (void) intlist.pop();
        intlist.print();
        intlist.clear();
        intlist.push(58);
        intlist.push(58);
        intlist.push(58);
        {
            size_t size = intlist.size();
            intlist[size - 1] = 1258;
        }
        intlist.print();
    }
    catch (char const* a) {
        std::cout << a << std::endl;
    }

#ifdef EXTENDED_TYPES
    try {
        floatlist.push(33.1);
        floatlist.push(58.2);
        for (uint32_t i = 0 ; i < 20 ; i++) {
            floatlist.push(i*i*1.23 + 2.48);
        }
        floatlist.print();
        (void) floatlist.pop();
        floatlist.print();
        floatlist.clear();
    }
    catch (char const* a) {
        std::cout << a << std::endl;
    }

    try {
        octetlist.push(33);
        octetlist.push(58);
        for (uint32_t i = 0 ; i < 20 ; i++) {
            octetlist.push(i*i+2);
        }
        octetlist.print();
        (void) octetlist.pop();
        octetlist.print();
        octetlist.clear();
    }
    catch (char const* a) {
        std::cout << a << std::endl;
    }
#endif

    return 0;
}