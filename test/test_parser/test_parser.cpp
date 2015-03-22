#include "gtest/gtest.h"
#include "parser/parser.h"
#include <iostream>
#include <sstream>
using std::cout;
using std::endl;
using std::stringstream;
using std::string;

/*
 * Helper methods for Empty Statement
 */
void TraverseASTBLock(AST_Block *block);
void TraverseASTSt(AST_Statement *st);

void TraverseASTBLock(AST_Block *block) {
    cout << "{";
    for (AST_Statement *st : block->statements) {
        TraverseASTSt(st);
    }
    cout << "}";
}

void TraverseASTSt(AST_Statement *st) {
    if (st->block) {
        TraverseASTBLock(st->block);
    }
    else cout << ";";
}

/*
 * Helper methods for Expression
 */
// AST_Expression* TraverseASTExpHelper(AST_Expression *exp);
// AST_Expression* TraverseASTExp(AST_Expression* exp);
//
// AST_Expression* CalcInt(int o1, OP op, int o2) {
//     int res = 0;
//     switch(op) {
//     case OP_ADD:
//         res = o1+o2;
//         break;
//     case OP_SUB:
//         res = o1-o2;
//         break;
//     case OP_MUL:
//         res = o1*o2;
//         break;
//     case OP_DIV:
//         if (o2 == 0) {
//             std::cout << "Error in CalcInt: divide zero" << std::endl;
//             exit(0);
//         }
//         res = o1/o2;
//         break;
//     default:
//         cout << "Error in test_parser: default" << endl;
//         exit(0);
//     }
//     Constant con(res);
//     return new AST_Expression(res);
// }
//
// Operand CalcDouble(double o1, OP op, double o2) {
//     double res = 0;
//     switch(op) {
//     case OP_ADD:
//         res = o1+o2;
//         break;
//     case OP_SUB:
//         res = o1-o2;
//         break;
//     case OP_MUL:
//         res = o1*o2;
//         break;
//     case OP_DIV:
//         if (o2 == 0) {
//             std::cout << "Error in CalcDouble: divide zero" << std::endl;
//             exit(0);
//         }
//         res = o1/o2;
//         break;
//     default:
//         cout << "Error in test_parser: default" << endl;
//         exit(0);
//     }
//     Constant con(res);
//     return new AST_Expression(con);
// }

/* deal with the expression whose operand are both numbers */
// AST_Expression* TraverseASTExpHelper(AST_Expression *exp) {
//     AST_Expression* e1 = exp->e1;
//     AST_Expression* e2 = exp->e2;
//     if (e1->o.type != e2->o.type) {
//         if (e1->o.type == CONST_INT) {
//             e1->o.type = CONST_DOUBLE;
//             e1->o.val.d = e1->o.val.i;
//         }
//         if (e2->o.type == CONST_INT) {
//             e2->o.type = CONST_DOUBLE;
//             e2->o.val.d = e2->o.val.i;
//         }
//     }
//     switch(o1.type) {
//         case EXP_INT:
//             return CalcInt(e1->o.val.i, exp->op, e2->o.val.i);
//             break;
//         case EXP_DOUBLE:
//             return CalcDouble(e1->o.val.d, exp->op, e2->o.val.d);
//             break;
//         default: ;
//     }
// }
//
// AST_Expression* TraverseASTExp(AST_Expression* exp) {
//     if (exp->is_leaf)
//         return exp->o;
//
//     AST_Expression *e1 = exp->e1;
//     AST_Expression *e2 = exp->e2;
//     if (e1->is_leaf && e2->is_leaf)
//         return TraverseASTExpHelper(exp);
//     else if (!e1->is_leaf && e2->is_leaf) {
//         AST_Expression *e = TraverseASTExp(e1);
//         return TraverseASTExpHelper(new AST_Expression(e, exp->op, e2));
//     }
//     else if (e1->is_leaf && !e2->is_leaf) {
//         Operand o = TraverseASTExp(e2);
//         return TraverseASTExpHelper(new AST_Expression(e1, exp->op, e));
//     }
//     else {
//         AST_Expression* _e1 = TraverseASTExp(e1);
//         AST_Expression* _e2 = TraverseASTExp(e2);
//         return TraverseASTExpHelper(new AST_Expression(_e1, exp->op, _e2));
//     }
// }


/* Print out the AST_EXPRESSION */
void PrintASTExp(AST_Expression *exp);
void PrintASTExpOperand(Operand o);

void PrintASTExpOperand(Operand o) {
    if (!o.GetPrefix().empty() || !o.GetSuffix().empty()) {
        cout << "(";
        for (OP op : o.GetPrefix()) {
            switch(op) {
                case OP_ADD:
                    cout << "+";
                    break;
                case OP_SUB:
                    cout << "-";
                    break;
                case OP_INC:
                    cout << "++";
                    break;
                case OP_DEC:
                    cout << "--";
                    break;
                case OP_NOT:
                    cout << "!";
                    break;
                default: ;
            }
        }
    }
    switch(o.GetType()) {
        case CONST_INT:
            cout << o.GetInt();
            break;
        case CONST_DOUBLE:
            cout << o.GetDouble();
            break;
        default:
            break;
    }
    if (!o.GetPrefix().empty() || !o.GetSuffix().empty()) {
        for (OP op : o.GetSuffix()) {
            switch(op) {
                case OP_INC:
                    cout << "++";
                    break;
                case OP_DEC:
                    cout << "--";
                    break;
                default: ;
            }
        }
        cout << ")";
    }
}
void PrintASTExp(AST_Expression *exp) {
    if (exp->is_leaf) {
        PrintASTExpOperand(exp->o);
        return;
    }
    if (!exp->e1->is_leaf)
        cout << "(";
    PrintASTExp(exp->e1);
    if (!exp->e1->is_leaf)
        cout << ")";
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
    if (!exp->e2->is_leaf)
        cout << "(";
    PrintASTExp(exp->e2);
    if (!exp->e2->is_leaf)
        cout << ")";
}


/*
 * Test Case
 */
TEST(test_parser, empty_block) {
    Parser parser("../test/test_parser/parser_test1.txt");
    stringstream ss;
    auto buf = cout.rdbuf();
    cout.rdbuf(ss.rdbuf());

    while (true) {
        AST_Statement *st = parser.ParseStatement();
        if (!st) break;
        TraverseASTSt(st);
    }

    cout.rdbuf(buf);
    EXPECT_EQ(";{};{;}{;};;;{}{}{};;;{;}{;{{;};}}", ss.str());
}

TEST(test_parser, declaration) {
    Parser parser("../test/test_parser/parser_test2.txt");

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
    auto buf = cout.rdbuf();
    cout.rdbuf(ss.rdbuf());

    AST_Statement *st;

    // 10+27-16+2.1;
    st = parser.ParseStatement();
    PrintASTExp((AST_Expression*) st);
    cout << endl;
    // e = TraverseASTExp((AST_Expression*) st);
    // EXPECT_EQ(CONST_DOUBLE, e->o.GetType());
    // EXPECT_EQ(23.1, e->o.val.dv);

    // 2*(2+3);
    st = parser.ParseStatement();
    PrintASTExp((AST_Expression*) st);
    cout << endl;
    // e = TraverseASTExp((AST_Expression*) st);
    // EXPECT_EQ(CONST_INT, e->o.GetType());
    // EXPECT_EQ(10, e->o.val.iv);

    // 128 * 4 / 3;
    st = parser.ParseStatement();
    PrintASTExp((AST_Expression*) st);
    cout << endl;
    // e = TraverseASTExp((AST_Expression*) st);
    // EXPECT_EQ(CONST_INT, e->o.GetType());
    // EXPECT_EQ(170, e->o.val.iv);

    // 10 + 128 * 4 - 16 + 10 / 2;
    st = parser.ParseStatement();
    PrintASTExp((AST_Expression*) st);
    cout << endl;
    // e = TraverseASTExp((AST_Expression*) st);
    // EXPECT_EQ(CONST_INT, e->o.GetType());
    // EXPECT_EQ(511, e->o.val.iv);

    cout.rdbuf(buf);
    string str = "((10+27)-16)+2.1\n"
        "2*(2+3)\n"
        "(128*4)/3\n"
        "10+(((128*4)-16)+(10/2))\n";
    EXPECT_EQ(str, ss.str());
}


TEST(test_parser, expression_with_unary_op) {
    Parser parser("../test/test_parser/parser_test5.txt");

    AST_Statement *st;
    Operand o;
    string s("(-7)+8\n"
            "5+(-6)\n"
            "(-3)+(+4)\n"
            "(++1----)-(-2++)\n");
    stringstream ss;
    auto buf_bak = cout.rdbuf();
    cout.rdbuf(ss.rdbuf());

    // -7+8;
    st = parser.ParseStatement();
    PrintASTExp((AST_Expression*) st);
    cout << endl;
    // 5+-6;
    st = parser.ParseStatement();
    PrintASTExp((AST_Expression*) st);
    cout << endl;
    // -3++4;
    st = parser.ParseStatement();
    PrintASTExp((AST_Expression*) st);
    cout << endl;
    // ++1------2++;
    st = parser.ParseStatement();
    PrintASTExp((AST_Expression*) st);
    cout << endl;

    cout.rdbuf(buf_bak);
    EXPECT_EQ(s, ss.str());
}
