#ifndef PARSER_H
#define PARSER_H

#include "lexer/token.h"

class AST_Block;
class AST_Statement;
class AST_Var;
class AST_Func;

enum ST {
    ST_EMPTY,
    ST_BLOCK,
    ST_VAR,
    ST_FUNC
};

class AST_Statement {
public:
    AST_Statement(ST _type, AST_Block *_block) : type(_type), block(_block) {};

    ST type;
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

class AST_Var : public AST_Statement {
public:
    AST_Var(ST _type, std::string _id, bool _is_array = false, int _sz_array = -1)
        : AST_Statement(_type, NULL), id(_id), is_array(_is_array), sz_array(_sz_array) {}

    std::string id;
    bool is_array;
    int sz_array;
};

class AST_Func : public AST_Statement {
public:
    AST_Func(ST _type, std::string _id, std::vector<AST_Var*> _paras = {})
        : AST_Statement(_type, NULL), id(_id), paras(_paras) {}

    std::string id;
    std::vector<AST_Var*> paras;
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
    AST_Var* ParseVar();
    AST_Func* ParseFunc();

private:
    bool EatToken(TOKEN t);

    Lexer lexer;
};


#endif


