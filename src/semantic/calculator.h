#ifndef CALCULATOR_H
#define CALCULATOR_H
#include "parser/parser.h"
#include "symbol.h"
#include "reader.h"
#include "exp.h"
#include "arithmetic.h"
#include "command.h"

class Command;
class CommInterprete;
class CommNewSymbolTable;
class CommDelSymbolTable;
class CommNewFuncSymbolTable;
class CommDelFuncSymbolTable;

class Calculator {
public:
    Calculator() {
        cur_sym = &g_sym;
    }

    vector<Command*> IntrStatement(AST_Statement *st);
    void IntrVar(AST_Statement *st);
    void IntrFunc(AST_Func* func);
    vector<Command*> IntrBlock(AST_Block* block);
    Constant IntrArrayContent(AST_Array *array);

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

class Command {
public:
    virtual vector<Command*> Execute(Calculator &calc) = 0;
};

class CommInterprete : public Command {
public:
    CommInterprete(AST_Statement *_st) : st(_st) {}

    vector<Command*> Execute(Calculator &calc);

private:
    AST_Statement *st;
};

class CommNewSymbolTable : public Command {
public:
    vector<Command*> Execute(Calculator &calc);
};

class CommDelSymbolTable : public Command {
public:
    vector<Command*> Execute(Calculator &calc);
};

class CommNewFuncSymbolTable : public Command {
public:
    vector<Command*> Execute(Calculator &calc);
};

class CommDelFuncSymbolTable : public Command {
public:
    vector<Command*> Execute(Calculator &calc);
};

#endif
