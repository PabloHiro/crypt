cmake_minimum_required (VERSION 2.8.12 FATAL_ERROR)

project(crypt CXX)

enable_language(C CXX)
enable_testing()

# Must use GNUInstallDirs to install libraries into correct
# locations on all platforms.
#include(GNUInstallDirs)

add_subdirectory(tests)

add_library(crypt STATIC
    src/base_crypt.cpp
    src/caesar.cpp
)

target_include_directories(crypt PUBLIC
    $<INSTALL_INTERFACE:include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE src
)

# If we have compiler requirements for this library, list them here
# target_compile_features(crypt
# )
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -static-libgcc -static-libstdc++")

# Depend on a library that we defined in the top-level file
# target_link_libraries(crypt
# )

# 'make install' to the correct locations (provided by GNUInstallDirs).
# install(TARGETS crypt EXPORT crypt_config
    # ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    # LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    # RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR})  # This is for Windows
# install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})


# This makes the project importable from the install directory
# Put config file in per-project dir (name MUST match), can also
# just go into 'cmake'.
#install(EXPORT crypt_config DESTINATION share/crypt/cmake)

# This makes the project importable from the build directory
#export(TARGETS crypt FILE crypt_config.cmake)