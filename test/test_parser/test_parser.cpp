#include "gtest/gtest.h"
#include "parser/parser.h"
#include <iostream>
#include <sstream>
using std::cout;
using std::endl;
using std::stringstream;

void TraverseASTBLock(AST_Block *block, stringstream &ss);
void TraverseASTSt(AST_Statement *st, stringstream &ss);

void TraverseASTBLock(AST_Block *block, stringstream &ss) {
    ss << "{";
    for (AST_Statement *st : block->statements) {
        TraverseASTSt(st, ss);
    }
    ss << "}";
}

void TraverseASTSt(AST_Statement *st, stringstream &ss) {
    if (st->block) {
        TraverseASTBLock(st->block, ss);
    }
    else ss << ";";
}

TEST(test_parser, empty_block) {
    Parser parser("./parser_test1.txt");
    stringstream ss;
    while (true) {
        AST_Statement *st = parser.ParseStatement();
        if (!st) break;
        TraverseASTSt(st, ss);
    }

    EXPECT_EQ(";{};{;}{;};;;{}{}{};;;{;}{;{{;};}}", ss.str());
}

TEST(test_parser, declaration) {
    Parser parser("./parser_test2.txt");
    stringstream ss;
    std::vector<ST> vtest = {ST_FUNC, ST_VAR, ST_VAR, ST_FUNC, ST_FUNC};
    int itest = 0;
    while (true) {
        AST_Statement *st = parser.ParseStatement();
        if (!st) break;
        EXPECT_EQ(vtest[itest++], st->type);
    }
}

