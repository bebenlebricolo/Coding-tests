WARNING_FLAGS=-Wall -Wextra
LINKED_LIBRARY=pthread
SOURCE_NAME=multi-threading
COMPILER_CXX=g++
CXX_STANDARD=c++17
RELEASE_OPTIMISATIONS=O3


all : release debug

release : ${SOURCE_NAME}.cpp
	mkdir -p Release
	${COMPILER_CXX} ${SOURCE_NAME}.cpp -o Release/${SOURCE_NAME} ${WARNING_FLAGS} -l${LINKED_LIBRARY} -${RELEASE_OPTIMISATIONS} -std=${CXX_STANDARD}

debug : ${SOURCE_NAME}.cpp
	mkdir -p Debug
	${COMPILER_CXX} ${SOURCE_NAME}.cpp -o Debug/${SOURCE_NAME} ${WARNING_FLAGS} -l${LINKED_LIBRARY} -g -std=${CXX_STANDARD}
