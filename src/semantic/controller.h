#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "interpreter.h"

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
private:
    bool is_debug;
    deque<AST_Statement*> qst;
    Parser parser;
    Interpreter intr;
};

#endif
