cmake_minimum_required(VERSION 3.10)
project(ContainerTests)

set(GTEST_DIR "C:/trkurs/bigproject/googletest")

add_subdirectory(${GTEST_DIR})
include_directories(${GTEST_DIR}/googletest/include)
include_directories(.)

add_executable(run_tests test.cpp)
target_link_libraries(run_tests gtest gtest_main)

if(MINGW)
    find_package(Threads REQUIRED)
    target_link_libraries(run_tests Threads::Threads)
endif()
