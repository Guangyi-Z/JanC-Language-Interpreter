set(AST_SRC operand.cpp) 
add_library(ast ${AST_SRC})
target_link_libraries(ast op)
