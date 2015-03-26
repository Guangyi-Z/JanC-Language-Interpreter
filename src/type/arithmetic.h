#ifndef ARITHMETIC_H
#define ARITHMETIC_H
#include "constant.h"

class Int;
class Double;
class String;

class Int : public Arithmetic {
public:
    Int() : Arithmetic(CONST_INT) {}
    Int(int _i) : Int() { i = _i;}

    int GetInt() { return i;}
    void SetInt(int v) { i = v;}

    /* virtual methods */
    Constant* ToNegative() { return new Int(-i);}
    Constant* ToInc()      { return new Int(i+1);}
    Constant* ToDec()      { return new Int(i-1);}

    Arithmetic* Add(Arithmetic* o2) { return o2->GetType() == CONST_INT? AddInt((Int*)o2) : AddDouble((Double*)o2);}
    Arithmetic* Sub(Arithmetic* o2) { return o2->GetType() == CONST_INT? AddInt((Int*)o2) : AddDouble((Double*)o2);}
    Arithmetic* Mul(Arithmetic* o2) { return o2->GetType() == CONST_INT? AddInt((Int*)o2) : AddDouble((Double*)o2);}
    Arithmetic* Div(Arithmetic* o2) { return o2->GetType() == CONST_INT? AddInt((Int*)o2) : AddDouble((Double*)o2);}

    Bool* GT   ( Arithmetic* o2) { return o2->GetType()==CONST_INT? GTInt((Int*)o2) : GTDouble((Double*)o2);}
    Bool* GTEQ ( Arithmetic* o2) { return o2->GetType()==CONST_INT? GTEQInt((Int*)o2) : GTEQDouble((Double*)o2);}
    Bool* LT   ( Arithmetic* o2) { return o2->GetType()==CONST_INT? LTInt((Int*)o2) : LTDouble((Double*)o2);}
    Bool* LTEQ ( Arithmetic* o2) { return o2->GetType()==CONST_INT? LTEQInt((Int*)o2) : LTEQDouble((Double*)o2);}
    Bool* EQ   ( Arithmetic* o2) { return o2->GetType()==CONST_INT? EQInt((Int*)o2) : EQDouble((Double*)o2);}
    Bool* NEQ  ( Arithmetic* o2) { return o2->GetType()==CONST_INT? NEQInt((Int*)o2) : NEQDouble((Double*)o2);}

    /* helper methods */
    Arithmetic* AddInt(Int* o2);
    Arithmetic* SubInt(Int* o2);
    Arithmetic* MulInt(Int* o2);
    Arithmetic* DivInt(Int* o2);
    Arithmetic* AddDouble(Double* o2);
    Arithmetic* SubDouble(Double* o2);
    Arithmetic* MulDouble(Double* o2);
    Arithmetic* DivDouble(Double* o2);

    Bool* GTInt   ( Int* o2 );
    Bool* GTEQInt ( Int* o2 );
    Bool* LTInt   ( Int* o2 );
    Bool* LTEQInt ( Int* o2 );
    Bool* EQInt   ( Int* o2 );
    Bool* NEQInt  ( Int* o2 );
    Bool* GTDouble   ( Double* o2 );
    Bool* GTEQDouble ( Double* o2 );
    Bool* LTDouble   ( Double* o2 );
    Bool* LTEQDouble ( Double* o2 );
    Bool* EQDouble   ( Double* o2 );
    Bool* NEQDouble  ( Double* o2 );
private:
    int i;
};

class Double : public Arithmetic {
public:
    Double() : Arithmetic(CONST_DOUBLE) {}
    Double(double _d) : Double() { d = _d;}

    double GetDouble() { return d;}
    void SetDouble(double v) { d = v;}

    /* virtual methods */
    Constant* ToNegative() { return new Double(-d);}
    Constant* ToInc()      { return new Double(d+1);}
    Constant* ToDec()      { return new Double(d-1);}

    Arithmetic* Add(Arithmetic* o2) { return o2->GetType() == CONST_INT? AddInt((Int*)o2) : AddDouble((Double*)o2);}
    Arithmetic* Sub(Arithmetic* o2) { return o2->GetType() == CONST_INT? AddInt((Int*)o2) : AddDouble((Double*)o2);}
    Arithmetic* Mul(Arithmetic* o2) { return o2->GetType() == CONST_INT? AddInt((Int*)o2) : AddDouble((Double*)o2);}
    Arithmetic* Div(Arithmetic* o2) { return o2->GetType() == CONST_INT? AddInt((Int*)o2) : AddDouble((Double*)o2);}

    Bool* GT   ( Arithmetic* o2) { return o2->GetType()==CONST_INT? GTInt((Int*)o2) : GTDouble((Double*)o2);}
    Bool* GTEQ ( Arithmetic* o2) { return o2->GetType()==CONST_INT? GTEQInt((Int*)o2) : GTEQDouble((Double*)o2);}
    Bool* LT   ( Arithmetic* o2) { return o2->GetType()==CONST_INT? LTInt((Int*)o2) : LTDouble((Double*)o2);}
    Bool* LTEQ ( Arithmetic* o2) { return o2->GetType()==CONST_INT? LTEQInt((Int*)o2) : LTEQDouble((Double*)o2);}
    Bool* EQ   ( Arithmetic* o2) { return o2->GetType()==CONST_INT? EQInt((Int*)o2) : EQDouble((Double*)o2);}
    Bool* NEQ  ( Arithmetic* o2) { return o2->GetType()==CONST_INT? NEQInt((Int*)o2) : NEQDouble((Double*)o2);}

    /* helper methods */
    Arithmetic* AddInt(Int* o2);
    Arithmetic* SubInt(Int* o2);
    Arithmetic* MulInt(Int* o2);
    Arithmetic* DivInt(Int* o2);
    Arithmetic* AddDouble(Double* o2);
    Arithmetic* SubDouble(Double* o2);
    Arithmetic* MulDouble(Double* o2);
    Arithmetic* DivDouble(Double* o2);

    Bool* GTInt   ( Int* o2 );
    Bool* GTEQInt ( Int* o2 );
    Bool* LTInt   ( Int* o2 );
    Bool* LTEQInt ( Int* o2 );
    Bool* EQInt   ( Int* o2 );
    Bool* NEQInt  ( Int* o2 );
    Bool* GTDouble   ( Double* o2 );
    Bool* GTEQDouble ( Double* o2 );
    Bool* LTDouble   ( Double* o2 );
    Bool* LTEQDouble ( Double* o2 );
    Bool* EQDouble   ( Double* o2 );
    Bool* NEQDouble  ( Double* o2 );
private:
    double d;
};


class String : public Arithmetic {
public:
    String() : Arithmetic(CONST_STRING) {}
    String(string _s) : String() { s = _s;}

    string GetString() { return s;}
    void SetString(string v) { s = v;}

    /* virtual methods */
    Constant* ToNegative() { cerr << "Error: incorrect op on type String" << endl; return NULL;}
    Constant* ToInc()      { cerr << "Error: incorrect op on type String" << endl; return NULL;}
    Constant* ToDec()      { cerr << "Error: incorrect op on type String" << endl; return NULL;}

    Arithmetic* Add(Arithmetic* o2) {
        switch(o2->GetType()) {
            case CONST_INT:
                return AddInt((Int*)o2);
            case CONST_DOUBLE:
                return AddDouble((Double*)o2);
            case CONST_STRING:
                return AddString((String*)o2);
            default: ;
        }
        return NULL;    /* never been here */
    }
    Arithmetic* Sub(Arithmetic* o2) { cerr << "Error: incorrect op on type String" << endl; return NULL;}
    Arithmetic* Mul(Arithmetic* o2) { cerr << "Error: incorrect op on type String" << endl; return NULL;}
    Arithmetic* Div(Arithmetic* o2) { cerr << "Error: incorrect op on type String" << endl; return NULL;}

    Bool* GT   ( Arithmetic* o2) { return new Bool(this->GetString() >  ((String*)o2)->GetString());}
    Bool* GTEQ ( Arithmetic* o2) { return new Bool(this->GetString() >= ((String*)o2)->GetString());}
    Bool* LT   ( Arithmetic* o2) { return new Bool(this->GetString() <  ((String*)o2)->GetString());}
    Bool* LTEQ ( Arithmetic* o2) { return new Bool(this->GetString() <= ((String*)o2)->GetString());}
    Bool* EQ   ( Arithmetic* o2) { return new Bool(this->GetString() == ((String*)o2)->GetString());}
    Bool* NEQ  ( Arithmetic* o2) { return new Bool(this->GetString() != ((String*)o2)->GetString());}

    /* helper methods */
    Arithmetic* AddInt(Int* o2);
    Arithmetic* AddDouble(Double* o2);
    Arithmetic* AddString(String* o2);
private:
    string s;
};
#endif
