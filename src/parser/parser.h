#ifndef PARSER_H
#define PARSER_H

#include "lexer/token.h"
class AST_Block;
class AST_Statement;

class AST_Statement {
public:
    AST_Statement(AST_Block *_block) : block(_block) {};

    AST_Block *block;
};

class AST_Block {
public:
    AST_Block(){};
    void AddStatement(AST_Statement* st) {
        statements.push_back(st);
    }

    std::vector<AST_Statement*> statements;
};

class Parser {
public:
    Parser(){};
    Parser(std::string path_to_file) {
        Load(path_to_file);
    }
    ~Parser() {};
    void Load(std::string path_to_file) {
        lexer.Load(path_to_file);
        lexer.GetNextToken();
    }
    void Parse();
    AST_Statement* ParseStatement();
    AST_Block* ParseBlock();

private:
    bool EatToken(TOKEN t);

    Lexer lexer;
};


#endif


