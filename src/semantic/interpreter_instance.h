#ifndef INTERPRETER_INSTANCE_H
#define INTERPRETER_INSTANCE_H
#include "interpreter.h"

class InterpreterInstance {
public:
    InterpreterInstance() {}

    void IntrStatement(AST_Statement *st) {
        Interpreter::IntrStatement(st, &sym, &fsym, &ret_val);
    }
private:

    NestedSymbolTable sym;
    FuncTable fsym;
    Constant *ret_val = NULL;
};

#endif
