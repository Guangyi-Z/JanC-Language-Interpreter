#ifndef OPERAND_H
#define OPERAND_H

#include "lexer/op.h"
#include "constant.h"

class AST_Expression;
class AST_Func;
class AST_Var;

enum OPRD_T {
    OPRD_LITERAL,
    OPRD_REF
};

class Operand {
public:
    Operand (OPRD_T t) : type(t) {}

    OPRD_T GetType()               { return type;}

    void AddPrefixOP(OP op)        { prefix.push_back(op);}
    void AddSuffixOP(OP op)        { suffix.push_back(op);}
    void SetPrefixOP(vector<OP> v) { prefix = v;}
    void SetSuffixOP(vector<OP> v) { suffix = v;}
    vector<OP> GetPrefix()         { return prefix;}
    vector<OP> GetSuffix()         { return suffix;}

    /* virtual functions */
    virtual void ToNegative() = 0;
    virtual void ToInc()      = 0;
    virtual void ToDec()      = 0;

private:
    OPRD_T type;
    std::vector<OP> prefix, suffix;
};

class Literal : public Operand {
public:
    Literal () : Operand(OPRD_LITERAL) { }
    Literal (Constant _con) : Operand(OPRD_LITERAL) { SetConst(_con);}

    void SetConst (Constant _con)   { con = _con;}
    Constant GetConst()             { return con;}
    CONST_T GetLiteralType()        { return con.GetType();}

    int GetInt()                    { return con.GetInt();}
    double GetDouble()              { return con.GetDouble();}
    char GetChar()                  { return con.GetChar();}
    string GetString()              { return con.GetString();}
    vector<int> GetArrayInt()       { return con.GetArrayInt();}
    vector<double> GetArrayDouble() { return con.GetArrayDouble();}

    virtual void ToNegative() { con.ToNegative();}
    virtual void ToInc()      { con.ToInc();}
    virtual void ToDec()      { con.ToDec();}

private:
    Constant con;
};

class Reference : public Operand {
public:
    Reference (string _id) : Operand(OPRD_REF) { id = _id;}

    void AddParameter(AST_Expression *e) {
        vp.push_back(e);
    }

    bool IsEmptyParameter()                 { return vp.empty();}
    int GetNumOfParameter()                 { return vp.size();}
    string GetID()                          { return id;}
    vector<AST_Expression*> GetParameters() { return vp;}

    /* todo */
    virtual void ToNegative() { }
    virtual void ToInc()      { }
    virtual void ToDec()      { }

private:
    string id;
    vector<AST_Expression*> vp;
};

#endif
