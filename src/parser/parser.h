#ifndef PARSER_H
#define PARSER_H

#include <map>
#include "lexer/token.h"
#include "exp.h"
using std::string;
using std::vector;

class AST_Block;
class AST_Statement;
class AST_Var;
class AST_Func;
class AST_Expression;

enum ST {
    ST_EMPTY,
    ST_BLOCK,
    ST_VAR,
    ST_FUNC,
    ST_EXP
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

    vector<AST_Statement*> statements;
};

class AST_Var : public AST_Statement {
public:
    AST_Var() : AST_Statement(ST_VAR, NULL) {}
    AST_Var(string _id, Constant _con)
        : AST_Statement(ST_VAR, NULL),
          id(_id),
          con(_con) {}
    void SetVar(string _id, Constant _con) {
        id = _id;
        con = _con;
    }

    string id;
    Constant con;
};

class AST_Func : public AST_Statement {
public:
    AST_Func(string _id, vector<string> _paras = {})
        : AST_Statement(ST_FUNC, NULL),
          id(_id),
          paras(_paras) {}

    std::string id;
    std::vector<string> paras;
};

// class AST_Expression : public AST_Statement {
// public:
//     AST_Expression()
//         : AST_Statement(ST_EXP, NULL),
//           op(OP_NONE) {}
//     AST_Expression(Operand _o1)
//         : AST_Statement(ST_EXP, NULL),
//           o1(_o1),
//           op(OP_NONE),
//           is_leaf(true){}
//     AST_Expression(Operand _o1, OP _op, Operand _o2)
//         : AST_Statement(ST_EXP, NULL),
//           o1(_o1),
//           o2(_o2),
//           op(_op),
//           is_leaf(false){}
//
//     Operand o1, o2;
//     OP op;
//     bool is_leaf;
// };

class AST_Expression : public AST_Statement {
public:
    AST_Expression(Operand _o)
        : AST_Statement(ST_EXP, NULL),
          op(OP_NONE),
          o(_o),
          is_leaf(true){}
    AST_Expression(AST_Expression* _e1, OP _op, AST_Expression* _e2)
        : AST_Statement(ST_EXP, NULL),
          e1(_e1),
          e2(_e2),
          op(_op),
          is_leaf(false){}

    AST_Expression *e1, *e2;
    OP op;
    // For the leaf expression
    Operand o;
    bool is_leaf;
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

    AST_Expression* ParseExpression();
    OP GetNextOP();
    AST_Expression* GetNextOperand();
    AST_Expression* ParseExpressionHelper(AST_Expression* e1, OP op);

private:
    bool EatToken(TOKEN t);

    Lexer lexer;
    OpProperty pp;
};


#endif


