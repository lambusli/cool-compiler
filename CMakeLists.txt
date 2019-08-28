cmake_minimum_required(VERSION 3.6)
project(midd_cool C CXX)

# Enable ExternalProject CMake module
include(ExternalProject)
enable_testing()
include(CTest) 

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

if(APPLE)
    include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/PlatformMacOS.cmake)
elseif(UNIX)
    include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/PlatformLinuxGCC.cmake)
else()
    message(WARNING "Unsupported platform/compiler combination")
endif()

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find appropriate Flex and Bison executables and libraries
find_package(BISON)
find_package(FLEX 2.5.35 REQUIRED)

# Download and compile external libraries
# spdlog Logging Library
ExternalProject_Add(
    spdlog
    URL https://github.com/gabime/spdlog/archive/v1.3.1.tar.gz
    PREFIX ${CMAKE_CURRENT_BINARY_DIR}/external/spdlog
    CONFIGURE_COMMAND ""
    BUILD_IN_SOURCE 1
    BUILD_COMMAND ""
    INSTALL_COMMAND ""
)
ExternalProject_Get_Property(spdlog source_dir)
set(SPDLOG_INCLUDE_DIR ${source_dir}/include)
include_directories(${SPDLOG_INCLUDE_DIR})

add_library(libspdlog INTERFACE)
add_dependencies(libspdlog spdlog)

# fmtlib String Formatting Library
ExternalProject_Add(
  fmtlib
  URL https://github.com/fmtlib/fmt/archive/5.3.0.tar.gz
  PREFIX ${CMAKE_CURRENT_BINARY_DIR}/external/fmtlib
  CMAKE_ARGS "-DFMT_TEST=OFF"
  UPDATE_COMMAND ""
  INSTALL_COMMAND ""
)
ExternalProject_Get_Property(fmtlib source_dir binary_dir)
set(FMTLIB_INCLUDE_DIR ${source_dir}/include)
set(FMTLIB_LIB_DIR ${binary_dir})
include_directories(${FMTLIB_INCLUDE_DIR})

add_library(libfmt IMPORTED STATIC GLOBAL)
add_dependencies(libfmt fmtlib)

# Set libfmt properties
set_target_properties(libfmt PROPERTIES
    "IMPORTED_LOCATION" "${FMTLIB_LIB_DIR}/libfmt.a"
)

# Set some useful compiler flags for all targets
set_directory_properties(PROPERTIES
    COMPILE_DEFINITIONS "$<$<CONFIG:Debug>:DEBUG>"
)
add_compile_options("-Wall;-Wno-unused-function")
include_directories(BEFORE ${CMAKE_CURRENT_SOURCE_DIR}/src/include)

add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(pa2)
add_subdirectory(pa3)
add_subdirectory(pa4)
add_subdirectory(pa5)
add_subdirectory(pax)
