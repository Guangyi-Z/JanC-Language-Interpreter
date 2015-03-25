#include "controller.h"

/********************************************
 * Interfaces
 *******************************************/
bool InterpreterController::HasNextStatement() {
    if (qst.empty())
        return false;
    return true;
}

void InterpreterController::NextStatement() {
    if (HasNextStatement()) {
        AST_Statement* st = qst.front();
        qst.pop_front();
        qc.AddCommand(st);
        if (!is_debug)
            qc.ContinueCommand();
    }
}

void InterpreterController::Continue() {
    while(HasNextStatement())
        NextStatement();
}

