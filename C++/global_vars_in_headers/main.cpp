#include <iostream>
#include "globals.hpp"
#include "globals_in_monolithic_header.hpp"
#include "utils.hpp"

using namespace std;

int main()
{
    print_globals();
    increment_globals();
    print_globals();

    cout << "\n\nModifiying globals in main() function\n\n";

    global_1 = 33 ;
    global_2 = 44 ;

    global_monolithic_1 = -48;
    global_monolithic_2 = -23;


    print_globals();

    return 0;
}