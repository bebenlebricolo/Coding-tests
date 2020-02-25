SOURCES=test.cpp
INCLUDES=-I"${GTEST_INCLUDE_DIRS}/../"
LIB_FOLDER=-L"C:\\Program Files (x86)\\googletest-distribution\\lib"
LIBRARIES=-lgtestd  \
		  -lgtest_maind



CXX_COMPILER=g++
CXX_WARNING_FLAGS=-Wall \
			      -Wextra \
				  -std=c++17
CXX_BUILD_CONFIGURATION=-g

all : test.o
	$(CXX_COMPILER) test.o $(INCLUDES) $(CXX_WARNING_FLAGS) $(CXX_BUILD_CONFIGURATION) $(LIB_FOLDER) $(LIBRARIES)

test.o :
	$(CXX_COMPILER) $(SOURCES) $(INCLUDES) $(CXX_WARNING_FLAGS) $(CXX_BUILD_CONFIGURATION) -c