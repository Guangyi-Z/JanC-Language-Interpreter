#include "interpreter.h"

/********************************************
 * Interfaces
 *******************************************/
bool Interpreter::HasNextStatement() {
    if (qst.empty())
        return false;
    return true;
}

void Interpreter::NextStatement() {
    if (HasNextStatement()) {
        AST_Statement* st = qst.front();
        qst.pop_front();
        qc.AddCommand(st);
        if (!is_debug)
            qc.ContinueCommand();
    }
}

void Interpreter::Continue() {
    while(HasNextStatement())
        NextStatement();
}

