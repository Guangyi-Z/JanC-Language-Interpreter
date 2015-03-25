#ifndef COMMAND_QUEUE_H
#define COMMAND_QUEUE_H
#include "parser/ast.h"
#include "calculator.h"
#include <deque>
using std::deque;

class CommQueue {
public:

    void AddCommand(AST_Statement* st);
    bool HasNextCommand();
    void ExecNextCommand();
    void ContinueCommand();

    /* reader */
    SymbolReader GetSymbolReader() { return calc.GetSymbolReader();}

private:
    void AddDerivedCommand(vector<Command*> vc);

    Calculator calc;
    deque<Command*> qt;
};

#endif
