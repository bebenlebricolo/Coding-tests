

all : main_GCC-7_with_shared-GCC-5 main_GCC-5_with_shared-GCC-7

main_GCC-7_with_shared-GCC-5: shared_GCC-5
	g++-7 main.cpp -o main_gcc7_shared_gcc5 -lshared_gcc5 -L.

shared_GCC-5 :
	g++-5 -fPIC -shared shared.cpp -o libshared_gcc5.so

main_GCC-5_with_shared-GCC-7: shared_GCC-7
	g++-5 main.cpp -o main_gcc5_shared_gcc7 -lshared_gcc7 -L.

shared_GCC-7 :
	g++-7 -fPIC -shared shared.cpp -o libshared_gcc7.so