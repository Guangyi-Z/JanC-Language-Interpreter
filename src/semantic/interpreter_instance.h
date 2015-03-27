#ifndef INTERPRETER_INSTANCE_H
#define INTERPRETER_INSTANCE_H
#include "interpreter.h"

class InterpreterInstance {
public:
    InterpreterInstance() {}

    void IntrStatement(AST_Statement *st) {
        Interpreter::IntrStatement(st, &sym, &fsym);
    }
private:

    NestedSymbolTable sym;
    FuncTable fsym;
};

#endif
