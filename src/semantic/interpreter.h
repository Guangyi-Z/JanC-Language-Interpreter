#ifndef INTERPRETER_H
#define INTERPRETER_H
#include <deque>
#include "ast/ast.h"
#include "symbol/symbol.h"
#include "operand_handler.h"
using std::deque;
using std::cerr;

/* static util class */
class Interpreter {
public:
    static void IntrStatement(AST_Statement *st, NestedSymbolTable *sym, FuncTable *fsym, Constant **back);
    static void IntrVar(AST_Statement *st, NestedSymbolTable *sym, FuncTable *fsym, Constant **back);
    static void IntrFunc(AST_Func* func, NestedSymbolTable *sym, FuncTable *fsym);
    static void IntrBlock(AST_Block* block, NestedSymbolTable *sym, FuncTable *fsym, Constant **back);
    static void IntrIf(AST_If* ifs, NestedSymbolTable *sym, FuncTable *fsym, Constant **back);
    static void IntrWhile(AST_While* sw, NestedSymbolTable *sym, FuncTable *fsym, Constant **back);
    static Constant* IntrAssignment(AST_Expression* exp, NestedSymbolTable *sym, FuncTable *fsym, Constant **back);
    static Constant* IntrExpression(AST_Expression* e, NestedSymbolTable *sym, FuncTable *fsym, Constant **back);
    static Constant* IntrOperand(Operand *o, NestedSymbolTable *sym, FuncTable *fsym, Constant **back);
    static Constant* IntrArrayContent(AST_Array *array, NestedSymbolTable *sym, FuncTable *fsym, Constant **back);

    static Constant* DoBinaryOP(Constant* con1, Constant *con2, OP op);
private:
    Interpreter() {}

    static Constant *cBreak;
    static Constant *cContinue;
};

#endif
