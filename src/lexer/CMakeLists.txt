set(LEXER_SRC token.cpp) 
add_library(lexer ${LEXER_SRC})
target_link_libraries(lexer op)
