cmake_minimum_required(VERSION 3.20)

project(lab_04_variant_08 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

function(oop_flags target)
    if(MSVC)
        target_compile_options(${target} PRIVATE /W4 /Zi)
        target_link_options(${target} PRIVATE /DEBUG)
    else()
        target_compile_options(${target} PRIVATE -Wall -Wextra -Wpedantic -g)
    endif()
endfunction()

add_library(lab04_lib src/Figure.cpp src/Triangle.cpp src/Square.cpp src/Pentagon.cpp src/FigureCollection.cpp)
target_include_directories(lab04_lib PUBLIC src)
oop_flags(lab04_lib)

add_executable(lab04_main src/main.cpp)
target_link_libraries(lab04_main PRIVATE lab04_lib)
oop_flags(lab04_main)

include(FetchContent)
FetchContent_Declare(googletest GIT_REPOSITORY https://github.com/google/googletest.git GIT_TAG v1.15.2)
FetchContent_MakeAvailable(googletest)

if(CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang" AND CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL 21)
    target_compile_options(gtest PRIVATE -Wno-character-conversion)
endif()

enable_testing()
include(GoogleTest)

add_executable(lab04_tests tests/test_variant.cpp)
target_link_libraries(lab04_tests PRIVATE lab04_lib GTest::gtest_main)
oop_flags(lab04_tests)
gtest_discover_tests(lab04_tests)
