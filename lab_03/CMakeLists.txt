cmake_minimum_required(VERSION 3.20)

project(lab_03_variant_18 LANGUAGES CXX)

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

add_library(lab03_lib src/IPAddress.cpp src/IPAddressSet.cpp)
target_include_directories(lab03_lib PUBLIC src)
oop_flags(lab03_lib)

add_executable(lab03_main src/main.cpp)
target_link_libraries(lab03_main PRIVATE lab03_lib)
oop_flags(lab03_main)

include(FetchContent)
FetchContent_Declare(googletest GIT_REPOSITORY https://github.com/google/googletest.git GIT_TAG v1.15.2)
FetchContent_MakeAvailable(googletest)

enable_testing()
include(GoogleTest)

add_executable(lab03_tests tests/test_variant.cpp)
target_link_libraries(lab03_tests PRIVATE lab03_lib GTest::gtest_main)
oop_flags(lab03_tests)
gtest_discover_tests(lab03_tests)
