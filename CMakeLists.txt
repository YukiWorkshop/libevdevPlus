cmake_minimum_required(VERSION 3.0)
project(libevdevPlus)

set(CMAKE_CXX_STANDARD 11)
set(PROJECT_VERSION "0.1.0")
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
set(CPACK_PACKAGE_VERSION_MAJOR "0")
set(CPACK_PACKAGE_VERSION_MINOR "1")
set(CPACK_PACKAGE_VERSION_PATCH "0")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "An easy-to-use C++ event device library")
set(CPACK_PACKAGE_CONTACT "Yuki Workshop <https://github.com/YukiWorkshop>")
set(CMAKE_PROJECT_HOMEPAGE_URL "https://github.com/YukiWorkshop/libevdevPlus")
set(CPACK_DEBIAN_PACKAGE_HOMEPAGE ${CMAKE_PROJECT_HOMEPAGE_URL})
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libc6 (>= 2.14), libstdc++6 (>= 5.2)")
set(CPACK_PACKAGE_FILE_NAME ${PROJECT_NAME}_${PROJECT_VERSION}_${CPACK_DEBIAN_PACKAGE_ARCHITECTURE})
set(CPACK_DEBIAN_DEBUGINFO_PACKAGE yes)
set(CPACK_DEBIAN_COMPRESSION_TYPE "xz")
set(CPACK_GENERATOR "DEB;RPM;TXZ")
set(CPACK_SOURCE_GENERATOR "DEB;RPM;TXZ")
include(CPack)

include(GNUInstallDirs)

set(SOURCE_FILES
        evdevPlus.cpp
        evdevPlus.hpp CommonIncludes.hpp InputEvent.hpp Resource.cpp)

add_library(evdevPlus SHARED ${SOURCE_FILES})
add_library(evdevPlus_Static STATIC ${SOURCE_FILES})

set_target_properties(evdevPlus PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(evdevPlus PROPERTIES SOVERSION ${CPACK_PACKAGE_VERSION_MAJOR})
set_target_properties(evdevPlus_Static PROPERTIES OUTPUT_NAME evdevPlus)

add_executable(evdevPlus_test test.cpp)
target_link_libraries(evdevPlus_test evdevPlus)

configure_file(evdevPlus.pc.in evdevPlus.pc @ONLY)
install(TARGETS evdevPlus
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})

install(TARGETS evdevPlus_Static
        DESTINATION ${CMAKE_INSTALL_LIBDIR})

install(FILES evdevPlus.hpp InputEvent.hpp CommonIncludes.hpp DESTINATION include/evdevPlus/)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/evdevPlus.pc DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig/)
