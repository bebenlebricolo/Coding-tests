

all : forward_declare_a include_a

forward_declare_a :
	g++ main.cpp -o main_fwd -Wall -Wextra -DFORWARD_DECLARE_A -fdiagnostics-color=always

include_a :
	g++ main.cpp -o main_inc_a -Wall -Wextra -fdiagnostics-color=always
