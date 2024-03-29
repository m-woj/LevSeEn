cmake_minimum_required(VERSION 3.21)
project(GTests)

include_directories(${gtest_SOURCE_DIR}/include
                    ${gtest_SOURCE_DIR}
                    ../include
                    ${CMAKE_CURRENT_SOURCE_DIR}/include)

file(GLOB_RECURSE SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/../src/*.cpp)
file(GLOB_RECURSE TEST_SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)
add_executable(GTests ${SRC_FILES} ${TEST_SRC_FILES} main.cpp)

set_target_properties(GTests
        PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED YES)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(GTests gtest gtest_main Threads::Threads)

