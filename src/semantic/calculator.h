#ifndef CALCULATOR_H
#define CALCULATOR_H
#include <deque>
#include "parser/parser.h"
#include "symbol.h"
#include "reader.h"
#include "exp.h"
#include "arithmetic.h"
using std::deque;

enum TASK_T {
    TASK_ST,
    TASK_RM_SYMBOL_TABLE
};

class Task {
public:
    Task(TASK_T t) : type(t), p(NULL) {}
    Task(AST_Statement* st) : type(TASK_ST), p(st) {}

    TASK_T type;
    void *p;
};

class Calculator {
public:
    Calculator() {
        cur_sym = &g_sym;
    }

    void IntrStatement();
    void IntrVar(AST_Statement *st);
    void IntrFunc(AST_Func* func);
    Constant IntrArrayContent(AST_Array *array);
    void IntrBlock(AST_Block* block);

    /* interfaces */
    void ExecStatement(AST_Statement* st);
    bool HasNext();
    void ExecNext();
    void Continue();

    /* reader */
    SymbolReader GetSymbolReader() { return SymbolReader(cur_sym);}

private:
    AST_Statement* Next();

    SymbolTable g_sym;  // global symbol table
    SymbolTable *cur_sym;
    FuncTable fsym;

    deque<Task> qt;
};

#endif
