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
    Interpreter() {
        cur_sym = &g_sym;
    }

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

    void NewSymbolTable()     { cur_sym = new SymbolTable(cur_sym);}
    void DelSymbolTable()     { cur_sym = cur_sym->GetParent();}
    void NewFuncSymbolTable() { bak_sym = cur_sym; cur_sym = new SymbolTable(&g_sym);}
    void DelFuncSymbolTable() { cur_sym = bak_sym;}

    /* reader */
    SymbolReader GetSymbolReader() { return SymbolReader(cur_sym);}

private:

    SymbolTable g_sym;  // global symbol table
    SymbolTable *cur_sym, *bak_sym;
    FuncTable fsym;
};

#endif
