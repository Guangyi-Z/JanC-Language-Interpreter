set(PARSER_SRC parser.cpp) 
add_library(parser ${PARSER_SRC})
target_link_libraries(parser lexer type)

