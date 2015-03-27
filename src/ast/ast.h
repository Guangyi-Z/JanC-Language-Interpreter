#ifndef AST_H
#define AST_H
#include "operand.h"
#include <iostream>
#include <string>
#include <vector>
using std::string;
using std::vector;
using std::cerr;
using std::endl;

enum ST {
    ST_BLOCK,
    ST_VAR,
    ST_ARRAY,
    ST_FUNC,
    ST_EXP,
    ST_RETURN,
    ST_IF,
    ST_WHILE,
    ST_BREAK,
    ST_CONTINUE
};

class AST_Statement;
class AST_Block;
class AST_Var;
class AST_Array;
class AST_Func;
class AST_Expression;
class AST_Return;
class AST_If;
class AST_While;

class AST_Statement {
public:
    AST_Statement(ST _type) : type(_type) {};
    ST GetType() { return type;}

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
    AST_Var(string _id) : AST_Statement(ST_VAR), id(_id), val(NULL) {}
    AST_Var(string _id, AST_Expression *_e)
        : AST_Statement(ST_VAR), id(_id), val(_e) {}

    string id;
    AST_Expression *val;
};

class AST_Array : public AST_Statement {
public:
    AST_Array(string _id, int _sz)
        : AST_Statement(ST_ARRAY), id(_id), sz_array(_sz) {}

    void AddElement(AST_Expression *e) {
        if (ve.size() > sz_array) {
            cerr << "Error in AST_Array: too many elements for the array" << endl;
            exit(0);
        }
        ve.push_back(e);
    }

    string id;
    int sz_array;
    vector<AST_Expression*> ve;
};

class AST_Func : public AST_Statement {
public:
    AST_Func(string _id)
        : AST_Statement(ST_FUNC),
          id(_id) {}

    void AddArgument(string arg) {
        vp.push_back(arg);
    }
    void AddFunctionBody(AST_Block *_b) {
        block = _b;
    }

    std::string id;
    std::vector<string> vp;
    AST_Block *block;
};

class AST_Expression : public AST_Statement {
public:
    AST_Expression(Operand *_o)
        : AST_Statement(ST_EXP),
          o(_o),
          is_leaf(true){}
    AST_Expression(AST_Expression* _e1, OP _op, AST_Expression* _e2)
        : AST_Statement(ST_EXP),
          e1(_e1),
          e2(_e2),
          op(_op),
          is_leaf(false){}

    bool IsLeaf() { return is_leaf;}

    AST_Expression *e1, *e2;
    OP op;
    // For the leaf expression
    Operand *o;
    bool is_leaf;
};

class AST_Return : public AST_Statement {
public:
    AST_Return(AST_Expression *_e) : AST_Statement(ST_RETURN), e(_e) {}

    AST_Expression *e;
};

class AST_If : public AST_Statement {
public:
    AST_If(AST_Expression *_cond, AST_Statement* _e) : AST_Statement(ST_IF) {
        vcond.push_back(_cond);
        ve.push_back(_e);
        e_else = NULL;
    }
    void AddElseIf(AST_Expression *_cond, AST_Statement* _e) {
        vcond.push_back(_cond);
        ve.push_back(_e);
    }
    void AddElse(AST_Statement* _e) {
        e_else = _e;
    }

    /* getter */
    vector<AST_Expression*> GetConds() { return vcond;}
    vector<AST_Statement*> GetStams() { return ve;}
    AST_Statement* GetElse() { return e_else;}
private:
    vector<AST_Expression*> vcond;
    vector<AST_Statement*> ve;
    AST_Statement* e_else;
};

class AST_While : public AST_Statement {
public:
    AST_While(AST_Expression *_cond, AST_Statement *_block) : AST_Statement(ST_WHILE) {
        cond = _cond;
        block = _block;
    }

    /* getter */
    AST_Expression* GetCond() { return cond;}
    AST_Statement* GetBlock() { return block;}
private:
    AST_Expression *cond;
    AST_Statement *block;
};

#endif
