#include "command_queue.h"

/********************************************
 * Interfaces
 *******************************************/
void CommQueue::AddCommand(AST_Statement* st) {
    qt.push_back(new CommInterprete(st));
}

void CommQueue::AddDerivedCommand(vector<Command*> vc) {
    for (auto it = vc.rbegin(); it!=vc.rend(); it++)
        qt.push_front(*it);
}

void CommQueue::ExecNextCommand() {
    if(HasNextCommand()) {
        Command *c = qt.front();
        qt.pop_front();
        AddDerivedCommand(c->Execute(intr));
    }
}

bool CommQueue::HasNextCommand() {
    if (qt.empty())
        return false;
    return true;
}

void CommQueue::ContinueCommand() {
    while(HasNextCommand())
        ExecNextCommand();
}
