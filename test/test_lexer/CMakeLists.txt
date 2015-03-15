add_executable(test_lexer test_lexer.cpp)
target_link_libraries(test_lexer lexer)
add_gtest(test_lexer)
