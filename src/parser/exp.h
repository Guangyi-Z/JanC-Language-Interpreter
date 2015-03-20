#ifndef EXP_H
#define EXP_H
#include "lexer/op.h"
#include "constant.h"

class AST_Expression;
class AST_Func;
class AST_Var;

class Operand {
public:
    Operand () { }

    Operand (int _v)                          { SetOperand(_v);                                      }
    Operand (double _v)                       { SetOperand(_v);                                      }
    Operand (char _v)                         { SetOperand(_v);                                      }
    Operand (string _v)                       { SetOperand(_v);                                      }
    Operand (string _id, vector<void*> _para) { SetOperand(_id, _para);}

    void SetOperand (int _v)                          { con.SetValue(_v);}
    void SetOperand (double _v)                       { con.SetValue(_v);}
    void SetOperand (char _v)                         { con.SetValue(_v);}
    void SetOperand (string _v)                       { con.SetValue(_v);}
    void SetOperand (string _id, vector<void*> _para) {
        id = _id;
        for (void *p : _para) {
            parameters.push_back((AST_Expression*)p);
        }
    }

    void AddPrefixOP(OP op) {
        prefix.push_back(op);
    }
    void AddSuffixOP(OP op) {
        suffix.push_back(op);
    }

    vector<OP> GetPrefix() {return prefix;}
    vector<OP> GetSuffix() {return suffix;}
    CONST_T GetType()               { return con.GetType();}
    int GetInt()                    { return con.GetInt();}
    double GetDouble()              { return con.GetDouble();}
    char GetChar()                  { return con.GetChar();}
    string GetString()              { return con.GetString();}
    vector<int> GetArrayInt()       { return con.GetArrayInt();}
    vector<double> GetArrayDouble() { return con.GetArrayDouble();}

private:
    std::vector<OP> prefix, suffix;

    string id;
    Constant con;
    // For function
    vector<AST_Expression*> parameters;
};

#endif
