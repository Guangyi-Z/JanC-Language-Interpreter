set(INTERPRETER_SRC controller.cpp interpreter.cpp operand_handler.cpp) 
add_library(interpreter ${INTERPRETER_SRC})
target_link_libraries(interpreter symbol parser ast)
