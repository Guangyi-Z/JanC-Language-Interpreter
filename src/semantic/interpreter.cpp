#include "interpreter.h"

/********************************************
 * Interfaces
 *******************************************/
void Interpreter::AddStatement(AST_Statement *st) {
    qst.push_back(st);
}

bool Interpreter::HasNextStatement() {
    if (qst.empty())
        return false;
    return true;
}

void Interpreter::NextStatement() {
    if (HasNextStatement()) {
        AST_Statement* st = qst.front();
        qst.pop_front();
        calc.ExecStatement(st);
        if (!is_debug)
            calc.Continue();
    }
}

void Interpreter::Continue() {
    while(HasNextStatement())
        NextStatement();
}

