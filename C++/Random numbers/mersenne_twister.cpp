#include <random>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <fstream>
#include <vector>

#include <cstdlib>
#include <cstring>

// Copied from https://en.cppreference.com/w/cpp/algorithm/random_shuffle

static uint32_t parse_input(int argc, char** argv)
{
    uint32_t out = 0;
    for (uint8_t i = 0 ; i < (uint8_t) argc ; i++)
    {
        uint8_t length = strnlen(argv[i], 5);
        char arg[6];
        memcpy(arg ,argv[i], length);
        int convert = atoi(arg);
        if (convert < 0)
        {
            convert = 0;
        }
        if (uint32_t (convert) > out)
        {
            out = convert;
        }
    }

    return out;
}

int main(int argc, char ** argv)
{
    std::vector<int> v = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    std::mt19937 g(256);

    uint32_t iterations = parse_input(argc, argv);
    std::ofstream outfile;
    outfile.open("Output_mersenne_twister.txt", std::ofstream::out);

    if (iterations == 0)
    {
        iterations = 1;
    }

    for (uint8_t i = 0 ; i < iterations ; i++)
    {
        std::vector<int> shuffled = v;
        std::shuffle(shuffled.begin(), shuffled.end(), g);
        std::copy(shuffled.begin(), shuffled.end(), std::ostream_iterator<int>(outfile, " "));
        outfile << std::endl;
    }

    return 0;
}