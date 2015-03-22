#ifndef EXP_H
#define EXP_H
#include "parser/parser.h"
class Interpreter;

class Expression {
public:
    static Constant CalcExp(Interpreter &intr, AST_Expression *exp) {
        if (exp->is_leaf) {
            return CalcOperand(exp->o);
        }
        Constant con1 = CalcExp(exp->e1);
        Constant con2 = CalcExp(exp->e2);
        switch(exp->op) {
        case OP_ADD:
            return Constant::Add(con1, con2);
        case OP_SUB:
            return Constant::Sub(con1, con2);
        case OP_MUL:
            return Constant::Mul(con1, con2);
        case OP_DIV:
            return Constant::Div(con1, con2);
        default:
            return Constant();
        }
    }

private:
    void CheckType(Constant &con1, Constant &con2);
    void CheckOP(OP op, CONST_T t);

    void DoPrefixOP(Operand &o);
    void DoSuffixOP(Operand &o);

    Constant CalcVar(Interpreter &intr, Operand o);
    Constant CalcFunc(Interpreter &intr, Operand o);

    Constant CalcOperand(Interpreter &intr, Operand o) {
        Constant con;
        if (o.GetType() != CONST_NONE) {    // basic type
            DoPrefixOP(o);
            con = o.GetConst();  // con is independent of suffix operations
            DoSuffixOP(o);
        }
        else {  // reference type
            // var
            if (intr.ReadVar(o.GetID()))
                con = CalcVar(o);
            // func
            else if (intr.ReadFunc(o.GetID()))
                con = CalcFunc(o);
            else {
                cout << "Error in CalcOperand: symbol not defined- " << o.GetID() << endl;
                exit(0);
            }
        }
        return con;
    }
    void PrintASTExp(AST_Expression *exp) {
    }

};

#endif
