cmake_minimum_required(VERSION 3.16)
project(jsonTest)

add_executable(jsonTest
    jsonTest.cpp
)

target_include_directories(jsonTest PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/rapidjson/include
)
