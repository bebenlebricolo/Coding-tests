#ifndef GLOBALS_IN_MONOLITHIC_H
#define GLOBALS_IN_MONOLITHIC_H

extern int global_monolithic_1;
extern int global_monolithic_2;

// Does not work because each translation unit gets its own version of global_monolithic_n when linked.
// -> First utils.cpp gets compiled as a temporary *.o object () and received its own version of globals definition
// -> Then when main.cpp gets compiled, it also receives its own globals definition
// -> At link time : both .o files embeds their own definition of their globals -> 'multiple definitions' issue !

// int global_monolithic_1 = 22;
// int global_monolithic_2 = 55;


#endif