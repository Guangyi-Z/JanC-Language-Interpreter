set(INTERPRETER_SRC interpreter.cpp exp.cpp arithmetic.cpp reader.cpp) 
add_library(interpreter ${INTERPRETER_SRC})
target_link_libraries(interpreter parser)
