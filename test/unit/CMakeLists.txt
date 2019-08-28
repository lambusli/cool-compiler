# Adapted from http://kaizou.org/2014/11/gtest-cmake/

# We need thread support
find_package(Threads REQUIRED)

# Enable ExternalProject CMake module
include(ExternalProject)

# Download and install GoogleTest
ExternalProject_Add(
    gtest
    URL https://github.com/google/googletest/archive/master.zip
    PREFIX ${CMAKE_CURRENT_BINARY_DIR}/external/gtest
    # Disable install step
    INSTALL_COMMAND ""
)

# Get GTest source and binary directories from CMake project
ExternalProject_Get_Property(gtest source_dir binary_dir)

# Create a libgtest target to be used as a dependency by test programs
add_library(libgtest IMPORTED STATIC GLOBAL)
add_dependencies(libgtest gtest)

# Set libgtest properties
set_target_properties(libgtest PROPERTIES
    "IMPORTED_LOCATION" "${binary_dir}/lib/libgtest.a"
    "IMPORTED_LINK_INTERFACE_LIBRARIES" "${CMAKE_THREAD_LIBS_INIT}"
)

include_directories(
    BEFORE
    ${CMAKE_SOURCE_DIR}/src/include
)
include_directories("${CMAKE_BINARY_DIR}/src") # For Flex/Bison generated files
include_directories("${source_dir}/googletest/include")

file(GLOB TEST_SRCS *.cc)

add_executable(midd-cool-test
    ${TEST_SRCS}
    $<TARGET_OBJECTS:cool_objs>
)

target_link_libraries(midd-cool-test
    libgtest
    libfmt
    libspdlog
)

add_test(NAME midd-cool_unit_tests COMMAND $<TARGET_FILE:midd-cool-test>)


