cmake_minimum_required(VERSION 2.8)
project(libevdevPlus)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        evdevPlus.cpp
        evdevPlus.hpp CommonIncludes.hpp InputEvent.hpp Resource.cpp)

add_library(evdevPlus SHARED ${SOURCE_FILES})
add_library(evdevPlus_Static STATIC ${SOURCE_FILES})
set_target_properties(evdevPlus_Static PROPERTIES OUTPUT_NAME evdevPlus)

add_executable(evdevPlus_test test.cpp)
target_link_libraries(evdevPlus_test evdevPlus)

install(TARGETS evdevPlus evdevPlus_Static DESTINATION lib)
install(FILES evdevPlus.hpp InputEvent.hpp CommonIncludes.hpp DESTINATION include/evdevPlus/)