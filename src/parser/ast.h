#ifndef AST_H
#define AST_H
#include <string>
#include <vector>
using std::string;
using std::vector;

enum ST {
    ST_EMPTY,
    ST_BLOCK,
    ST_VAR,
    ST_FUNC,
    ST_EXP
};

class AST_Block;
class AST_Statement;
class AST_Var;
class AST_Func;
class AST_Expression;

class AST_Statement {
public:
    AST_Statement(ST _type) : type(_type) {};

    ST type;
};

class AST_Block : public AST_Statement {
public:
    AST_Block() : AST_Statement(ST_BLOCK) {};
    void AddStatement(AST_Statement* st) {
        statements.push_back(st);
    }

    vector<AST_Statement*> statements;
};

class AST_Var : public AST_Statement {
public:
    AST_Var(string _id, AST_Expression *_e)
        : AST_Statement(ST_VAR) {
        SetVar(_id, _e);
    }
    AST_Var(string _id, int _sz, vector<AST_Expression*> _ve)
        : AST_Statement(ST_VAR) {
        SetVar(_id, _sz, _ve);
    }

    void SetVar(string _id, AST_Expression *_e) {
        is_array = false;
        id = _id;
        ve.push_back(_e);
    }
    void SetVar(string _id, int _sz, vector<AST_Expression*> _ve) {
        is_array = true;
        id = _id;
        sz_array = _sz;
        ve = _ve;
    }

    string id;
    vector<AST_Expression*> ve;
    int sz_array;
    bool is_array;
};

class AST_Func : public AST_Statement {
public:
    AST_Func(string _id, vector<string> _paras = {})
        : AST_Statement(ST_FUNC),
          id(_id),
          paras(_paras) {}

    std::string id;
    std::vector<string> paras;
    AST_Block *block;
};

class AST_Expression : public AST_Statement {
public:
    AST_Expression(Operand _o)
        : AST_Statement(ST_EXP),
          op(OP_NONE),
          o(_o),
          is_leaf(true){}
    AST_Expression(AST_Expression* _e1, OP _op, AST_Expression* _e2)
        : AST_Statement(ST_EXP),
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

#endif
