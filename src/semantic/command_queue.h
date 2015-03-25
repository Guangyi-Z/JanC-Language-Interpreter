#ifndef COMMAND_QUEUE_H
#define COMMAND_QUEUE_H
#include "parser/ast.h"
#include "interpreter.h"
#include <deque>
using std::deque;

class CommQueue {
public:

    void AddCommand(AST_Statement* st);
    bool HasNextCommand();
    void ExecNextCommand();
    void ContinueCommand();

    /* reader */
    SymbolReader GetSymbolReader() { return intr.GetSymbolReader();}

private:
    void AddDerivedCommand(vector<Command*> vc);

    Interpreter intr;
    deque<Command*> qt;
};

#endif
