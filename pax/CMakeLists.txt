set(ast-lexer ${CMAKE_SOURCE_DIR}/src/ast-lexer.cpp)

# Flex-generated code uses deprecated features
set_source_files_properties(
    ${ast-lexer}
    PROPERTIES
    COMPILE_FLAGS -Wno-deprecated-register
)

add_executable(opt
    ${CMAKE_SOURCE_DIR}/pa5/cgen-main.cc
    ${ast-lexer}
    ${CMAKE_SOURCE_DIR}/src/ast-parser.cpp
    $<TARGET_OBJECTS:cool_objs>
)
set_target_properties(opt PROPERTIES OUTPUT_NAME "cgen")
target_link_libraries(opt libfmt libspdlog)