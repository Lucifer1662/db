cmake_minimum_required(VERSION 2.6)
 
# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})
 
file(GLOB SRC
     "*.h"
     "*.cpp"
)
add_executable(run_tests ${SRC})
target_link_libraries(run_tests ${GTEST_LIBRARIES} pthread db_core)
target_include_directories(run_tests PUBLIC "../db_core")

add_test(NAME run_tests COMMAND run_tests)