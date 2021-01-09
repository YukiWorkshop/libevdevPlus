cmake_minimum_required(VERSION 3.0)
project(libevdevPlus)

set(SOURCE_FILES
        evdevPlus.cpp evdevPlus.hpp CommonIncludes.hpp InputEvent.hpp Resource.cpp)

add_library(evdevPlus ${SOURCE_FILES})
target_include_directories(evdevPlus PUBLIC .)

add_executable(evdevPlus_test test.cpp)
target_link_libraries(evdevPlus_test evdevPlus)

configure_file(evdevPlus.pc.in evdevPlus.pc @ONLY)