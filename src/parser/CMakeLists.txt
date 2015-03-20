# set(SYMBOL_SRC symbol.cpp) 
# add_library(symbol ${SYMBOL_SRC})

set(PARSER_SRC parser.cpp) 
add_library(parser ${PARSER_SRC})
target_link_libraries(parser lexer)

