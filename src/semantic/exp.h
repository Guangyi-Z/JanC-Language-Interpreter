#ifndef EXP_H
#define EXP_H
#include "parser/parser.h"
#include "symbol.h"

class Expression {
public:
    static Constant CalcExp(SymbolTable &sym,
            FuncTable &fsym,
            AST_Expression *exp);

    static void DoPrefixOP(Operand *o);
    static void DoSuffixOP(Operand *o);

    static Constant CalcOperand(SymbolTable &sym, FuncTable &fsym, Operand *o);
    static Constant CalcVar(SymbolTable &sym, FuncTable &fsym, Operand *o);
    static Constant CalcFunc(SymbolTable &sym, FuncTable &fsym, Operand *o);
private:

};

#endif
