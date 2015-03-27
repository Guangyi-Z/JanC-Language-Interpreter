set(SYMBOL_SRC symbol.cpp) 
add_library(symbol ${SYMBOL_SRC})
target_link_libraries(symbol type)
