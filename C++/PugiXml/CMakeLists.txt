cmake_minimum_required(VERSION 3.1)
project(pugixmltest)

add_library(pugixmllib SHARED
    ${CMAKE_SOURCE_DIR}/pugixml/src/pugixml.cpp
)

target_include_directories(pugixmllib PUBLIC
    ${CMAKE_SOURCE_DIR}/pugixml/src
)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

#if (WIN32)
#
#    add_definitions(-DCMAKE_WINDOWS_EXPORT_ALL_SYMBOLS=TRUE)
#    add_definitions(-DBUILD_SHARED_LIBS=TRUE)
#    #set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS TRUE FORCE)
#    #set(BUILD_SHARED_LIBS TRUE FORCE)
#endif()

# Thanks to them for the tips!
# https://bytefreaks.net/programming-2/manually-set-the-cmake-output-folder
#set_target_properties(pugixmllib PROPERTIES
#    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
#    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
#    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
#)

# Export symbols from pugixml library without modifying its pugiconfig.hpp
if(WIN32)
    target_compile_definitions(pugixmllib
        PUBLIC "PUGIXML_API=__declspec(dllexport)"
    )
endif()

#link_directories(
#    ${CMAKE_BINARY_DIR}/bin
#    ${CMAKE_BINARY_DIR}/lib
#)

add_executable(fakeapp
    ${CMAKE_SOURCE_DIR}/App/app.cpp
    App/TotoTest.c
    App/TotoTest.h
 )

target_link_libraries(fakeapp
    pugixmllib
)

target_include_directories(fakeapp PRIVATE
    ${CMAKE_SOURCE_DIR}/pugixmllib/src
)
