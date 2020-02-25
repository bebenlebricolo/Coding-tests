#include <iostream>
#include "utils.hpp"
#include "globals.hpp"
#include "globals_in_monolithic_header.hpp"

using namespace std;

#define WORKS

#ifdef WORKS

// It is mandatory to define globals only once in one source code
int global_1 = 0;
int global_2 = 0;

// Same goes for them
int global_monolithic_1 = 0;
int global_monolithic_2 = 0;

#endif

void print_globals()
{
    cout << "Global 1 : " << global_1 << endl;
    cout << "Global 2 : " << global_2 << endl;
    cout << "Global monolithic 1 : " << global_monolithic_1 << endl;
    cout << "Global monolithic 2 : " << global_monolithic_2 << endl;
}

void increment_globals()
{
    global_1++;
    global_2++;

    global_monolithic_1++;
    global_monolithic_2++;
}