#include "gtest/gtest.h"
#include "parser/parser.h"
#include <iostream>
using std::cout;
using std::endl;

void TraverseASTSt(AST_Statement *st);
void TraverseASTBLock(AST_Block *block);

void TraverseASTBLock(AST_Block *block) {
    cout << "{" << endl;
    for (AST_Statement *st : block->statements) {
        TraverseASTSt(st);
    }
    cout << "}" << endl;
}

void TraverseASTSt(AST_Statement *st) {
    if (st->block) {
        TraverseASTBLock(st->block);
    }
    else cout << ";" << endl;
}

TEST(test_parser, empty_block) {
    Parser parser("./parser_test1.txt");
    while (true) {
        AST_Statement *st = parser.ParseStatement();
        if (!st) break;
        TraverseASTSt(st);
    }

    // EXPECT_EQ(TOK_INT, lexer.GetNextToken());
}

