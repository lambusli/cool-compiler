add_test(
    NAME lexer_integration_test
    COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/runner.sh ${CMAKE_CURRENT_SOURCE_DIR}/lexer
        ${CMAKE_CURRENT_SOURCE_DIR}/lexer-test.sh
        -L "$<TARGET_FILE:lexer>"
)

add_custom_target(
    lexer_test_ref
    find . -name '*.test' -exec bash -c '"${CMAKE_CURRENT_SOURCE_DIR}/lexer-test.sh" -L "${CMAKE_SOURCE_DIR}/bin/lexer" {} > {}.stdout 2> {}.stderr' \\\;
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/lexer"
)

# Use reference lexer by default. You can change the -L argument to use your lexer implementations
add_test(
    NAME parser_integration_test
    COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/runner.sh "${CMAKE_CURRENT_SOURCE_DIR}/parser"
        "${CMAKE_CURRENT_SOURCE_DIR}/parser-test.sh"
        -L "${CMAKE_SOURCE_DIR}/bin/lexer"
        -P "$<TARGET_FILE:parser>"
)

add_custom_target(
    parser_test_ref
    find . -name '*.test' -exec bash -c '${CMAKE_CURRENT_SOURCE_DIR}/parser-test.sh -L "${CMAKE_SOURCE_DIR}/bin/lexer" -P "${CMAKE_SOURCE_DIR}/bin/parser" {} > {}.stdout 2> {}.stderr' \\\;
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/parser"
)

# Use reference lexer and parser by default. You can change the -L and -P arguments to use your implementations
add_test(
    NAME semant_integration_test
    COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/runner.sh "${CMAKE_CURRENT_SOURCE_DIR}/semant"
        "${CMAKE_CURRENT_SOURCE_DIR}/semant-test.sh"
        -L "${CMAKE_SOURCE_DIR}/bin/lexer"
        -P "${CMAKE_SOURCE_DIR}/bin/parser"
        -S "$<TARGET_FILE:semant>"
)

add_custom_target(
    semant_test_ref
    find . -name '*.test' -exec bash -c '${CMAKE_CURRENT_SOURCE_DIR}/semant-test.sh -L "${CMAKE_SOURCE_DIR}/bin/lexer" -P "${CMAKE_SOURCE_DIR}/bin/parser" -S "${CMAKE_SOURCE_DIR}/bin/semant" {} > {}.stdout 2> {}.stderr' \\\;
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/semant"
)

# Use reference components by default. You can change the -L, -P, and -S arguments to use your implementations
add_test(
    NAME cgen_integration_test
    COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/runner.sh -s "${CMAKE_CURRENT_SOURCE_DIR}/cgen"
    "${CMAKE_CURRENT_SOURCE_DIR}/cgen-test.sh"
    -L "${CMAKE_SOURCE_DIR}/bin/lexer"
    -P "${CMAKE_SOURCE_DIR}/bin/parser"
    -S "${CMAKE_SOURCE_DIR}/bin/semant"
    -C "$<TARGET_FILE:cgen>"
    -M "${CMAKE_SOURCE_DIR}/bin/cool-spim"
    -H "${CMAKE_SOURCE_DIR}/bin/trap.handler"
)

add_custom_target(
    cgen_test_ref
    find . -name '*.test' -exec bash -c '${CMAKE_CURRENT_SOURCE_DIR}/cgen-test.sh -L "${CMAKE_SOURCE_DIR}/bin/lexer" -P "${CMAKE_SOURCE_DIR}/bin/parser" -S "${CMAKE_SOURCE_DIR}/bin/semant" -C "${CMAKE_SOURCE_DIR}/bin/cgen" -M "${CMAKE_SOURCE_DIR}/bin/cool-spim" -H "${CMAKE_SOURCE_DIR}/bin/trap.handler" {} > {}.stdout 2> {}.stderr' \\\;
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/cgen"
)