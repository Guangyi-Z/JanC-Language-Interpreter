#include "gtest/gtest.h"
#include "parser/parser.h"
#include <iostream>
#include <sstream>
using std::cout;
using std::endl;
using std::stringstream;

/*
 * Helper methods for Empty Statement
 */
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

/*
 * Helper methods for Expression
 */
AST_ExpressionOperand TraverseASTExpHelper(AST_Expression *exp);
AST_ExpressionOperand TraverseASTExp(AST_Expression* exp);

AST_ExpressionOperand CalcInt(int o1, OP op, int o2) {
    AST_ExpressionOperand o;
    o.type = EXP_INT;
    switch(op) {
    case OP_ADD:
        o.val.iv = o1+o2;
        break;
    case OP_SUB:
        o.val.iv = o1-o2;
        break;
    case OP_MUL:
        o.val.iv = o1*o2;
        break;
    case OP_DIV:
        if (o2 == 0) {
            std::cout << "Error in CalcInt: divide zero" << std::endl;
            exit(0);
        }
        o.val.iv = o1/o2;
        break;
    default: break;
    }
    return o;
}

AST_ExpressionOperand CalcDouble(double o1, OP op, double o2) {
    AST_ExpressionOperand o;
    o.type = EXP_DOUBLE;
    switch(op) {
    case OP_ADD:
        o.val.dv = o1+o2;
        break;
    case OP_SUB:
        o.val.dv = o1-o2;
        break;
    case OP_MUL:
        o.val.dv = o1*o2;
        break;
    case OP_DIV:
        if (o2 == 0) {
            std::cout << "Error in CalcDouble: divide zero" << std::endl;
            exit(0);
        }
        o.val.dv = o1/o2;
        break;
    default: break;
    }
    return o;
}

/* deal with the expression whose operand are both numbers */
AST_ExpressionOperand TraverseASTExpHelper(AST_Expression *exp) {
    AST_ExpressionOperand &o1 = exp->o1;
    AST_ExpressionOperand &o2 = exp->o2;
    if (o1.type != o2.type) {
        if (o1.type == EXP_INT) {
            o1.type = EXP_DOUBLE;
            o1.val.dv = o1.val.iv;
        }
        if (o2.type == EXP_INT) {
            o2.type = EXP_DOUBLE;
            o2.val.dv = o2.val.iv;
        }
    }
    AST_ExpressionOperand res;
    switch(o1.type) {
        case EXP_INT:
            res = CalcInt(o1.val.iv, exp->op, o2.val.iv);
            break;
        case EXP_DOUBLE:
            res = CalcDouble(o1.val.dv, exp->op, o2.val.dv);
            break;
        default:
            break;
    }
    return res;
}

AST_ExpressionOperand TraverseASTExp(AST_Expression* exp) {
    if (exp->is_leaf)
        return exp->o1;

    AST_ExpressionOperand &o1 = exp->o1;
    AST_ExpressionOperand &o2 = exp->o2;
    if (o1.type != EXP_EXP && o2.type != EXP_EXP)
        return TraverseASTExpHelper(exp);
    else if (o1.type == EXP_EXP && o2.type != EXP_EXP) {
        AST_ExpressionOperand o = TraverseASTExp(o1.val.ev);
        return TraverseASTExpHelper(new AST_Expression(o, exp->op, o2));
    }
    else if (o1.type != EXP_EXP && o2.type == EXP_EXP) {
        AST_ExpressionOperand o = TraverseASTExp(o2.val.ev);
        return TraverseASTExpHelper(new AST_Expression(o1, exp->op, o));
    }
    else {
        AST_ExpressionOperand _o1 = TraverseASTExp(o1.val.ev);
        AST_ExpressionOperand _o2 = TraverseASTExp(o2.val.ev);
        return TraverseASTExpHelper(new AST_Expression(_o1, exp->op, _o2));
    }
}

/* Print out the AST_EXPRESSION */
void PrintASTExp(AST_Expression *exp);
void PrintASTExpOperand(AST_ExpressionOperand o);

void PrintASTExpOperand(AST_ExpressionOperand o) {
    switch(o.type) {
        case EXP_INT:
            cout << o.val.iv;
            break;
        case EXP_DOUBLE:
            cout << o.val.dv;
            break;
        case EXP_EXP:
            cout << "(";
            PrintASTExp(o.val.ev);
            cout << ")";
            break;
        default:
            break;
    }
}
void PrintASTExp(AST_Expression *exp) {
    if (exp->is_leaf) {
        PrintASTExpOperand(exp->o1);
        return;
    }
    PrintASTExpOperand(exp->o1);
    switch(exp->op) {
    case OP_ADD:
        cout << "+";
        break;
    case OP_SUB:
        cout << "-";
        break;
    case OP_MUL:
        cout << "*";
        break;
    case OP_DIV:
        cout << "/";
        break;
    default:
        break;
    }
    PrintASTExpOperand(exp->o2);
}

/*
 * Test Case
 */
TEST(test_parser, empty_block) {
    Parser parser("../test/test_parser/parser_test1.txt");
    stringstream ss;
    while (true) {
        AST_Statement *st = parser.ParseStatement();
        if (!st) break;
        TraverseASTSt(st, ss);
    }

    EXPECT_EQ(";{};{;}{;};;;{}{}{};;;{;}{;{{;};}}", ss.str());
}

TEST(test_parser, declaration) {
    Parser parser("../test/test_parser/parser_test2.txt");
    stringstream ss;
    std::vector<ST> vtest = {ST_FUNC, ST_VAR, ST_VAR, ST_FUNC, ST_FUNC};
    int itest = 0;
    while (true) {
        AST_Statement *st = parser.ParseStatement();
        if (!st) break;
        EXPECT_EQ(vtest[itest++], st->type);
    }
}

TEST(test_parser, simple_expression) {
    Parser parser("../test/test_parser/parser_test3.txt");
    stringstream ss;

    AST_Statement *st;
    AST_ExpressionOperand o;
    // 10+27-16+2.1;
    st = parser.ParseStatement();
    PrintASTExp((AST_Expression*) st);
    cout << endl;
    o = TraverseASTExp((AST_Expression*) st);
    EXPECT_EQ(EXP_DOUBLE, o.type);
    EXPECT_EQ(23.1, o.val.dv);
    // 2*(2+3);
    st = parser.ParseStatement();
    PrintASTExp((AST_Expression*) st);
    cout << endl;
    o = TraverseASTExp((AST_Expression*) st);
    EXPECT_EQ(EXP_INT, o.type);
    EXPECT_EQ(10, o.val.iv);
    // 128 * 4 / 3;
    st = parser.ParseStatement();
    PrintASTExp((AST_Expression*) st);
    cout << endl;
    o = TraverseASTExp((AST_Expression*) st);
    EXPECT_EQ(EXP_INT, o.type);
    EXPECT_EQ(170, o.val.iv);
    // 10 + 128 * 4 - 16 + 10 / 2;
    st = parser.ParseStatement();
    PrintASTExp((AST_Expression*) st);
    cout << endl;
    o = TraverseASTExp((AST_Expression*) st);
    EXPECT_EQ(EXP_INT, o.type);
    EXPECT_EQ(511, o.val.iv);
}

