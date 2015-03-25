set(INTERPRETER_SRC interpreter.cpp exp.cpp arithmetic.cpp reader.cpp calculator.cpp command_queue.cpp command.cpp) 
add_library(interpreter ${INTERPRETER_SRC})
target_link_libraries(interpreter parser)
