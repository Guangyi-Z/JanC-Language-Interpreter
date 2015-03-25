set(INTERPRETER_SRC controller.cpp exp.cpp arithmetic.cpp reader.cpp interpreter.cpp) 
add_library(interpreter ${INTERPRETER_SRC})
target_link_libraries(interpreter parser)
