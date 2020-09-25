cmake_minimum_required(VERSION 3.1)
project(pugixml)

add_library(pugixml SHARED
    ${CMAKE_SOURCE_DIR}/pugixml/src/pugixml.cpp
)

target_include_directories(pugixml PUBLIC
    ${CMAKE_SOURCE_DIR}/pugixml/src
)

# Thanks to them for the tips!
# https://bytefreaks.net/programming-2/manually-set-the-cmake-output-folder
set_target_properties(pugixml PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)