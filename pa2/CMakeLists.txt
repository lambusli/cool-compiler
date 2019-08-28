# Run Flex on Cool Lexer
FLEX_TARGET(CoolLexer cool.flex ${CMAKE_CURRENT_BINARY_DIR}/cool-lexer.cpp COMPILE_FLAGS "-d")

# Flex-generated code uses deprecated features
set_source_files_properties(
    ${FLEX_CoolLexer_OUTPUTS}
    PROPERTIES
    COMPILE_FLAGS -Wno-deprecated-register
)

# Lexer is dependent on the parser and so we typically define the targets together
# and register the dependency (and add generate headers to the include path). However
# to enable separate assignments, the requisite header is pre-generated and provided
# as part of the skeleton.

add_executable(lexer
    lexer-main.cc
    ${FLEX_CoolLexer_OUTPUTS}
    $<TARGET_OBJECTS:cool_objs>
)
target_link_libraries(lexer libfmt libspdlog)