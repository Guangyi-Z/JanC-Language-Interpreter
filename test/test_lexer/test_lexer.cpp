#include "gtest/gtest.h"
#include "lexer/token.h"

TEST(test_lexer, number) {
    Lexer lexer("./lexer_test1.txt");

    EXPECT_EQ(TOK_INT, lexer.GetNextToken());
    EXPECT_EQ(TOK_INT, lexer.GetNextToken());
    EXPECT_EQ(TOK_INT, lexer.GetNextToken());
    EXPECT_EQ(TOK_DOUBLE, lexer.GetNextToken());
    EXPECT_EQ(TOK_INT, lexer.GetNextToken());
    EXPECT_EQ(TOK_INT, lexer.GetNextToken());
    EXPECT_EQ(TOK_INT, lexer.GetNextToken());
    EXPECT_EQ(TOK_INT, lexer.GetNextToken());
    EXPECT_EQ(TOK_INT, lexer.GetNextToken());
    EXPECT_EQ(TOK_INT, lexer.GetNextToken());
    EXPECT_EQ(TOK_DOUBLE, lexer.GetNextToken());
    EXPECT_EQ(TOK_DOUBLE, lexer.GetNextToken());
    EXPECT_EQ(TOK_DOUBLE, lexer.GetNextToken());
    EXPECT_EQ(TOK_INT, lexer.GetNextToken());
    EXPECT_EQ(TOK_DOUBLE, lexer.GetNextToken());
    EXPECT_EQ(TOK_DOUBLE, lexer.GetNextToken());
    EXPECT_EQ(TOK_INT, lexer.GetNextToken());
    EXPECT_EQ(TOK_INT, lexer.GetNextToken());
    EXPECT_EQ(TOK_INT, lexer.GetNextToken());
    EXPECT_EQ(TOK_DOUBLE, lexer.GetNextToken());
    EXPECT_EQ(TOK_DOUBLE, lexer.GetNextToken());
}

TEST(test_lexer, id) {
    Lexer lexer("./lexer_test2.txt");

    EXPECT_EQ(TOK_INT, lexer.GetNextToken());
    EXPECT_EQ(TOK_INT, lexer.GetNextToken());
    EXPECT_EQ(TOK_INT, lexer.GetNextToken());
    EXPECT_EQ(TOK_DOUBLE, lexer.GetNextToken());
    EXPECT_EQ(TOK_INT, lexer.GetNextToken());
    EXPECT_EQ(TOK_INT, lexer.GetNextToken());
    EXPECT_EQ(TOK_INT, lexer.GetNextToken());
    EXPECT_EQ(TOK_INT, lexer.GetNextToken());
    EXPECT_EQ(TOK_ID, lexer.GetNextToken());
    EXPECT_EQ(TOK_ID, lexer.GetNextToken());
    EXPECT_EQ(TOK_ID, lexer.GetNextToken());
    EXPECT_EQ(TOK_INT, lexer.GetNextToken());
    EXPECT_EQ(TOK_ID, lexer.GetNextToken());
    EXPECT_EQ(TOK_ID, lexer.GetNextToken());
    EXPECT_EQ(TOK_BOOL, lexer.GetNextToken());
    EXPECT_EQ(TOK_INT, lexer.GetNextToken());
    EXPECT_EQ(TOK_DOUBLE, lexer.GetNextToken());
    EXPECT_EQ(TOK_DOUBLE, lexer.GetNextToken());
    EXPECT_EQ(TOK_DOUBLE, lexer.GetNextToken());
    EXPECT_EQ(TOK_WHILE, lexer.GetNextToken());
    EXPECT_EQ(TOK_INT, lexer.GetNextToken());
    EXPECT_EQ(TOK_DOUBLE, lexer.GetNextToken());
    EXPECT_EQ(TOK_VAR, lexer.GetNextToken());
    EXPECT_EQ(TOK_DOUBLE, lexer.GetNextToken());
    EXPECT_EQ(TOK_VAR, lexer.GetNextToken());
    EXPECT_EQ(TOK_INT, lexer.GetNextToken());
    EXPECT_EQ(TOK_ID, lexer.GetNextToken());
    EXPECT_EQ(TOK_INT, lexer.GetNextToken());
    EXPECT_EQ(TOK_ID, lexer.GetNextToken());
    EXPECT_EQ(TOK_INT, lexer.GetNextToken());
    EXPECT_EQ(TOK_DOUBLE, lexer.GetNextToken());
    EXPECT_EQ(TOK_DOUBLE, lexer.GetNextToken());
}

TEST(test_lexer, delimeter) {
    Lexer lexer("./lexer_test3.txt");

    EXPECT_EQ(TOK_COMMA, lexer.GetNextToken());
    EXPECT_EQ(TOK_SEMI, lexer.GetNextToken());
    EXPECT_EQ(TOK_BRACE_LEFT, lexer.GetNextToken());
    EXPECT_EQ(TOK_BRACE_RIGHT, lexer.GetNextToken());
    EXPECT_EQ(TOK_PAREN_LEFT, lexer.GetNextToken());
    EXPECT_EQ(TOK_PAREN_RIGHT, lexer.GetNextToken());
    EXPECT_EQ(TOK_CURLY_BRACE_LEFT, lexer.GetNextToken());
    EXPECT_EQ(TOK_CURLY_BRACE_RIGHT, lexer.GetNextToken());
}

TEST(test_lexer, str) {
    Lexer lexer("./lexer_test4.txt");

    EXPECT_EQ(TOK_STRING, lexer.GetNextToken());
    EXPECT_EQ(TOK_STRING, lexer.GetNextToken());
    EXPECT_EQ(TOK_STRING, lexer.GetNextToken());
    EXPECT_EQ(TOK_STRING, lexer.GetNextToken());
}

TEST(test_lexer, operation) {
    Lexer lexer("./lexer_test5.txt");

    EXPECT_EQ(TOK_OP, lexer.GetNextToken());
    EXPECT_EQ(OP_SUB, lexer.GetCurOP());
    EXPECT_EQ(TOK_DOUBLE, lexer.GetNextToken());
    EXPECT_EQ(TOK_INT, lexer.GetNextToken());
    EXPECT_EQ(TOK_OP, lexer.GetNextToken());
    EXPECT_EQ(OP_INC, lexer.GetCurOP());
    EXPECT_EQ(TOK_INT, lexer.GetNextToken());
    EXPECT_EQ(TOK_PAREN_LEFT, lexer.GetNextToken());
    EXPECT_EQ(TOK_INT, lexer.GetNextToken());
    EXPECT_EQ(TOK_OP, lexer.GetNextToken());
    EXPECT_EQ(TOK_INT, lexer.GetNextToken());
    EXPECT_EQ(TOK_PAREN_RIGHT, lexer.GetNextToken());
    EXPECT_EQ(TOK_OP, lexer.GetNextToken());
    EXPECT_EQ(TOK_INT, lexer.GetNextToken());
    EXPECT_EQ(TOK_OP, lexer.GetNextToken());
    EXPECT_EQ(TOK_INT, lexer.GetNextToken());
    EXPECT_EQ(TOK_DOUBLE, lexer.GetNextToken());
    EXPECT_EQ(TOK_OP, lexer.GetNextToken());
    EXPECT_EQ(TOK_DOUBLE, lexer.GetNextToken());
    EXPECT_EQ(TOK_DOUBLE, lexer.GetNextToken());
    EXPECT_EQ(TOK_OP, lexer.GetNextToken());
    EXPECT_EQ(TOK_WHILE, lexer.GetNextToken());
    EXPECT_EQ(TOK_STRING, lexer.GetNextToken());
    EXPECT_EQ(TOK_IF, lexer.GetNextToken());
    EXPECT_EQ(TOK_PAREN_LEFT, lexer.GetNextToken());
    EXPECT_EQ(TOK_ID, lexer.GetNextToken());
    EXPECT_EQ(TOK_OP, lexer.GetNextToken());
    EXPECT_EQ(TOK_ID, lexer.GetNextToken());
    EXPECT_EQ(TOK_PAREN_RIGHT, lexer.GetNextToken());
    EXPECT_EQ(TOK_ID, lexer.GetNextToken());
    EXPECT_EQ(TOK_SEMI, lexer.GetNextToken());
    EXPECT_EQ(TOK_INT, lexer.GetNextToken());
    EXPECT_EQ(TOK_OP, lexer.GetNextToken());
    EXPECT_EQ(TOK_DOUBLE, lexer.GetNextToken());
}
