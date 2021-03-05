#include <omp.h>
#include <cstdint>
#include <iostream>

int main()
{
    uint64_t sum_with_reduction = 0;
    uint64_t sum_without_reduction = 0;
    const uint8_t max = 30;
    #pragma omp parallel for reduction(+:sum_with_reduction)
    for (uint8_t i = 0 ; i < max ; i++ )
    {
        sum_with_reduction += i * 2;
    }

    #pragma omp parallel for
    for (uint8_t i = 0 ; i < max ; i++ )
    {
        sum_without_reduction += i * 2;
    }

    // Sum of all integers from 0 to n is n(n+1)/2
    // As we start at 0, it becomes (n-1)*n /2
    uint64_t expected_sum = max * (max -1);
    std::cout << "expected sum = "<< expected_sum << std::endl
              << "sum with reduction = " << sum_with_reduction << std::endl
              << "sum without reduction = " << sum_without_reduction << std::endl;

    return 0;
}