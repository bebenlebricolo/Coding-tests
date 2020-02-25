SOURCES = 					\
	main.cpp				\
	c_functions.c			\
	c_interface.cpp			\
	class_collection.cpp	\

OUTFILE = c_cpp_mixup.exe
CXX_COMPILER = g++
CXX_FLAGS = -Wall -Wextra
ADDITIONAL_FLAGS=-fdiagnostics-color=always

all : $(SOURCES)
	$(CXX_COMPILER) $(SOURCES) $(CXX_FLAGS) $(ADDITIONAL_FLAGS) -o $(OUTFILE)

dbg : $(SOURCES)
	$(CXX_COMPILER) $(SOURCES) $(CXX_FLAGS) $(ADDITIONAL_FLAGS) -o $(OUTFILE) -g

