#ifndef CONTROLLER_H
#define CONTROLLER_H
#include "interpreter_instance.h"
#include "parser/parser.h"

class InterpreterController {
public:
    /* construtor */
    InterpreterController() {}
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
    deque<AST_Statement*> qst;
    Parser parser;
    InterpreterInstance intr;
};

#endif
