cmake_minimum_required(VERSION 3.0)

project(car_tests)

find_package(GTest REQUIRED)

enable_testing()

add_executable(battery_testing test_Battery.cpp)
target_include_directories(battery_testing PUBLIC
    ${CMAKE_SOURCE_DIR}/..
    ${CMAKE_SOURCE_DIR}/mocks
    ${GTEST_INCLUDES}
)

set(DEBUG_OPTIONS
    "-Wall"
    "-Wextra"
    "-g"
    "-Og"
)

set(RELEASE_OPTIONS
    "-Wall"
    "-Wextra"
    "-O3"
)

set (CMAKE_BUILD_TYPE Debug)
set (CMAKE_CXX_COMPILE_FEATURES ${DEBUG_OPTIONS})

target_link_libraries(battery_testing ${GTEST_LIBRARIES} pthread)