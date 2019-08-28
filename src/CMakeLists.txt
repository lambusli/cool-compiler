add_library(cool_objs
    OBJECT
    stringtab.cc
    utilities.cc
    ast.cc
    ast_consumer.cc
    semant.cc
    cgen.cc
    cgen_supp.cc
)
add_dependencies(cool_objs libfmt libspdlog)