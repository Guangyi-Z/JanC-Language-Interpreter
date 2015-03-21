set(INTERPRETER_SRC interpreter.cpp) 
add_library(interpreter ${INTERPRETER_SRC})
target_link_libraries(interpreter parser)
