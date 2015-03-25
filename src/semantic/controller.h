#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "interpreter.h"
#include "command_queue.h"

class InterpreterController {
public:
    /* construtor */
    InterpreterController() {
        is_debug = false;
    }
    InterpreterController(string path_to_file) : InterpreterController() { Load(path_to_file);}
    void Load(string path_to_file) {
        parser.Load(path_to_file);
        AST_Statement* st = parser.ParseStatement();
        while(st) {
            qst.push_back(st);
            st = parser.ParseStatement();
        }
    }

    /* interfaces */
    bool HasNextStatement();
    void NextStatement();
    void AddStatement(AST_Statement *st) { qst.push_back(st);}
    void Continue();

    /* debug */
    void SetDebugMode(bool b) { is_debug = b;}
    bool IsEndOfCommand() { return !qc.HasNextCommand();}
    void NextCommand() { qc.ExecNextCommand();}
    void ContinueCommand() { qc.ContinueCommand();}

    /* reader */
    SymbolReader GetSymbolReader() { return qc.GetSymbolReader();}

private:
    bool is_debug;
    CommQueue qc;
    deque<AST_Statement*> qst;
    Parser parser;
};

#endif
