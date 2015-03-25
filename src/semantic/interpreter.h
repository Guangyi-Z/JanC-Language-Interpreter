#ifndef INTERPRETER_H
#define INTERPRETER_H
#include <deque>
#include "parser/parser.h"
#include "symbol.h"
#include "reader.h"
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
    Constant IntrExpression(AST_Expression* e);
    Constant UnpackVar(Reference *r);
    Constant UnpackFunc(Reference *r);
    Constant IntrOperand(Operand *o);
    Constant IntrArrayContent(AST_Array *array);

    static void DoPrefixOP(Operand *o);
    static void DoSuffixOP(Operand *o);

    /* reader */
    SymbolReader GetSymbolReader() { return SymbolReader(sym.GetCurSymbolTable());}

private:

    NestedSymbolTable sym;
    FuncTable fsym;
};

#endif
