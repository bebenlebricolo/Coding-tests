cmake_minimum_required(VERSION 3.0)
project(simple_maths_tests)

enable_testing()
find_package(GTest REQUIRED)    

# set(GTEST_BASE_FOLDER "C:\\Program Files (x86)\\googletest-distribution")
# set(GTEST_DEBUG_LIBS_FOLDER "${GTEST_BASE_FOLDER}\\lib")
# set(GTEST_INCLUDES "${GTEST_BASE_FOLDER}\\include")
# message("Gtest includes folder : ${GTEST_INCLUDES}")

# list(APPEND GTEST_LIBRARIES
#     gtestd
#     gtest_maind
# )


# foreach(lib ${GTEST_LIBRARIES})
#     add_library(${lib} STATIC IMPORTED)
#     set_target_properties(${lib} PROPERTIES IMPORTED_LOCATION ${GTEST_DEBUG_LIBS_FOLDER}\\lib${lib}.a )
#     message("setting property for lib : ${GTEST_DEBUG_LIBS_FOLDER}\\lib${lib}.a")
#     if (EXISTS "${GTEST_DEBUG_LIBS_FOLDER}\\lib${lib}.a")
#         message("Found ${lib} ! ")
#     endif()
# endforeach(lib)


# find_library(${GTEST_DEBUG_LIBS_FOLDER} gtestd)
# find_library(${GTEST_DEBUG_LIBS_FOLDER} gtest_maind)
# find_library(${GTEST_DEBUG_LIBS_FOLDER} gmockd)
# find_library(${GTEST_DEBUG_LIBS_FOLDER} gmock_maind)

add_executable(simple_maths_tests test.cpp)
target_include_directories(simple_maths_tests PUBLIC ${GTEST_INCLUDES})
target_link_libraries(simple_maths_tests ${GTEST_LIBRARIES} pthread)