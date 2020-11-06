#include <iostream>

// Prevents that macro to be defined for a comparison with "this" object
#if ptr != this
#define TEST_PTR(ptr)                               \
    if (ptr == nullptr)                             \
    {                                               \
        std::cout << "nullptr found!" << std::endl; \
    }
#else
#define TEST_PTR(ptr) \
    {                 \
    }
#endif

struct toto
{
    int d;
    void test_this()
    {
        TEST_PTR(this); // shall warn about Wnonnull-compare because this is never null
    }
};

int main()
{
    toto t;
    t.test_this();
    int *mynonnullableint = &t.d;
    TEST_PTR(mynonnullableint);
    (void)mynonnullableint;
    return 0;
}