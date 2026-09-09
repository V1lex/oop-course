cmake_minimum_required(VERSION 3.20)

project(lab_01_variant_5 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

function(oop_flags target)
    if(MSVC)
        target_compile_options(${target} PRIVATE /W4 /Zi)
        target_link_options(${target} PRIVATE /DEBUG)
    else()
        target_compile_options(${target} PRIVATE -Wall -Wextra -Wpedantic -g)
    endif()
endfunction()

add_library(lab01_lib
    src/array_ops.cpp
)

target_include_directories(lab01_lib PUBLIC src)
oop_flags(lab01_lib)

add_executable(lab01_main
    main.cpp
)

target_link_libraries(lab01_main PRIVATE lab01_lib)
oop_flags(lab01_main)

include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.15.2
)

FetchContent_MakeAvailable(googletest)

enable_testing()
include(GoogleTest)

add_executable(lab01_tests
    tests/test_variant.cpp
)

target_link_libraries(lab01_tests PRIVATE
    lab01_lib
    GTest::gtest_main
)

oop_flags(lab01_tests)
gtest_discover_tests(lab01_tests)