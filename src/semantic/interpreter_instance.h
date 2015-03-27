#ifndef INTERPRETER_INSTANCE_H
#define INTERPRETER_INSTANCE_H
#include "interpreter.h"

class InterpreterInstance {
public:
    InterpreterInstance() {}

    void IntrStatement(AST_Statement *st) {
        Interpreter::IntrStatement(st, &sym, &fsym, &back);
    }
private:

    NestedSymbolTable sym;
    FuncTable fsym;
    /* when back is not NULL,
     * the following statements wont be interpreted.
     * This happens when return, break, continue. */
    Constant *back = NULL;
};

#endif
