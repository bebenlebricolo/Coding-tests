SOURCES = config.cpp io.cpp main.cpp mock_registers.cpp
OUTFILE = ioclass.exe
CXX_COMPILER = g++
CXX_FLAGS = -Wall -Wextra
ADDITIONAL_FLAGS=-fdiagnostics-color=always

all : $(SOURCES)
	$(CXX_COMPILER) $(SOURCES) $(CXX_FLAGS) $(ADDITIONAL_FLAGS) -o $(OUTFILE)
