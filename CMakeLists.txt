cmake_minimum_required(VERSION 3.17)

set(PROJECT_NAME stomplog)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(googletest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/src)

set(SOURCE
        Formatter.h
        Formatter.cpp
        Message.h
        Message.cpp
        )

set(TESTS
        MessageTest.cpp
        )

list(TRANSFORM TESTS PREPEND "tests/")
list(TRANSFORM SOURCE PREPEND "src/")

enable_testing()

add_library(${PROJECT_NAME} ${SOURCE})
add_executable(tests ${TESTS})
add_test(NAME first COMMAND tests)

target_link_libraries(tests gtest gtest_main ${PROJECT_NAME})