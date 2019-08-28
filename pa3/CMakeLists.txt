if (CMAKE_VERSION VERSION_GREATER "3.4")
    BISON_TARGET(CoolParser cool.y ${CMAKE_CURRENT_BINARY_DIR}/cool-parser.cpp
            COMPILE_FLAGS "-v -y -b cool --debug -p cool_yy"
            DEFINES_FILE "${CMAKE_CURRENT_BINARY_DIR}/cool-parser.hpp")
else()
    BISON_TARGET(CoolParser cool.y ${CMAKE_CURRENT_BINARY_DIR}/cool-parser.cpp
            COMPILE_FLAGS "-v -y -b cool --debug -p cool_yy"
            HEADER "${CMAKE_CURRENT_BINARY_DIR}/cool-parser.hpp")
endif()

set(token-lexer ${CMAKE_SOURCE_DIR}/src/token-lexer.cpp)

# Flex-generated code uses deprecated features
set_source_files_properties(
    ${token-lexer}
    PROPERTIES
    COMPILE_FLAGS -Wno-deprecated-register
)

add_executable(parser
    parser-main.cc
    ${token-lexer}
    ${BISON_CoolParser_OUTPUTS}
    $<TARGET_OBJECTS:cool_objs>
)
target_link_libraries(parser libfmt libspdlog)