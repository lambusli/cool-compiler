set(ast-lexer ${CMAKE_SOURCE_DIR}/src/ast-lexer.cpp)

# Flex-generated code uses deprecated features
set_source_files_properties(
    ${ast-lexer}
    PROPERTIES
    COMPILE_FLAGS -Wno-deprecated-register
)

add_executable(cgen
    cgen-main.cc
    ${ast-lexer}
    ${CMAKE_SOURCE_DIR}/src/ast-parser.cpp
    $<TARGET_OBJECTS:cool_objs>
)
target_link_libraries(cgen libfmt libspdlog)