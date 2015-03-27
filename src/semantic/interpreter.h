#ifndef INTERPRETER_H
#define INTERPRETER_H
#include <deque>
#include "parser/parser.h"
#include "symbol/symbol.h"
#include "arithmetic.h"
using std::deque;
using std::cerr;

class Interpreter {
public:
    Interpreter() {}

    void IntrStatement(AST_Statement *st);
    void IntrVar(AST_Statement *st);
    void IntrFunc(AST_Func* func);
    void IntrBlock(AST_Block* block);
    Constant* IntrExpression(AST_Expression* e);
    Constant* UnpackVar(Reference *r);
    Constant* UnpackFunc(Reference *r);
    Constant* IntrOperand(Operand *o);
    Constant* IntrArrayContent(AST_Array *array);
    Constant* DoBinaryOP(Constant* con1, Constant *con2, OP op);

    static void DoPrefixOP(Operand *o);
    static void DoSuffixOP(Operand *o);

private:

    NestedSymbolTable sym;
    FuncTable fsym;
};

#endif
