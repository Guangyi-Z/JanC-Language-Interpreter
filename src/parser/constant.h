#ifndef CONSTANT
#define CONSTANT
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
using std::string;
using std::vector;
using std::cout;
using std::cerr;
using std::endl;

enum CONST_T {
    CONST_BOOL,
    CONST_INT,
    CONST_DOUBLE,
    CONST_CHAR,
    CONST_STRING,
    CONST_ARRAY,
    CONST_NONE
};

class Constant;
class Arithmetic;
class Array;
class Int;
class Double;
class Bool;

class Constant {
public:
    /* construtor */
    Constant (CONST_T _t): type(_t) { }

    /* getter */
    CONST_T GetType()               { return type;}

    virtual Constant* ToNegative() { cerr << "Error: incorrect op for type- " << GetType() << endl; return NULL;}
    virtual Constant* ToInc()      { cerr << "Error: incorrect op for type- " << GetType() << endl; return NULL;}
    virtual Constant* ToDec()      { cerr << "Error: incorrect op for type- " << GetType() << endl; return NULL;}

    /* Printer */
    // void Print() = 0;
private:
    CONST_T type;
};

class Arithmetic: public Constant {
public:
    Arithmetic(CONST_T _t) : Constant(_t) {}

    virtual Arithmetic* Add(Arithmetic* o2) = 0;
    virtual Arithmetic* Sub(Arithmetic* o2) = 0;
    virtual Arithmetic* Mul(Arithmetic* o2) = 0;
    virtual Arithmetic* Div(Arithmetic* o2) = 0;

    virtual Bool* GT(Arithmetic* o2) = 0;
    virtual Bool* GTEQ(Arithmetic* o2) = 0;
    virtual Bool* LT(Arithmetic* o2) = 0;
    virtual Bool* LTEQ(Arithmetic* o2) = 0;
    virtual Bool* EQ(Arithmetic* o2) = 0;
    virtual Bool* NEQ(Arithmetic* o2) = 0;
private:
    ;
};

class Int : public Arithmetic {
public:
    Int() : Arithmetic(CONST_INT) {}
    Int(int _i) : Int() { i = _i;}

    int GetInt() { return i;}
    void SetInt(int v) { i = v;}

    virtual Constant* ToNegative() { return new Int(-i);}
    virtual Constant* ToInc()      { return new Int(i+1);}
    virtual Constant* ToDec()      { return new Int(i-1);}

    Arithmetic* Add(Arithmetic* o2) { return o2->GetType() == CONST_INT? AddInt((Int*)o2) : AddDouble((Double*)o2);}
    Arithmetic* Sub(Arithmetic* o2) { return o2->GetType() == CONST_INT? AddInt((Int*)o2) : AddDouble((Double*)o2);}
    Arithmetic* Mul(Arithmetic* o2) { return o2->GetType() == CONST_INT? AddInt((Int*)o2) : AddDouble((Double*)o2);}
    Arithmetic* Div(Arithmetic* o2) { return o2->GetType() == CONST_INT? AddInt((Int*)o2) : AddDouble((Double*)o2);}

    Arithmetic* AddInt(Int* o2);
    Arithmetic* SubInt(Int* o2);
    Arithmetic* MulInt(Int* o2);
    Arithmetic* DivInt(Int* o2);
    Arithmetic* AddDouble(Double* o2);
    Arithmetic* SubDouble(Double* o2);
    Arithmetic* MulDouble(Double* o2);
    Arithmetic* DivDouble(Double* o2);

    Bool* GT   ( Arithmetic* o2) { return o2->GetType()==CONST_INT? GTInt((Int*)o2) : GTDouble((Double*)o2);}
    Bool* GTEQ ( Arithmetic* o2) { return o2->GetType()==CONST_INT? GTEQInt((Int*)o2) : GTEQDouble((Double*)o2);}
    Bool* LT   ( Arithmetic* o2) { return o2->GetType()==CONST_INT? LTInt((Int*)o2) : LTDouble((Double*)o2);}
    Bool* LTEQ ( Arithmetic* o2) { return o2->GetType()==CONST_INT? LTEQInt((Int*)o2) : LTEQDouble((Double*)o2);}
    Bool* EQ   ( Arithmetic* o2) { return o2->GetType()==CONST_INT? EQInt((Int*)o2) : EQDouble((Double*)o2);}
    Bool* NEQ  ( Arithmetic* o2) { return o2->GetType()==CONST_INT? NEQInt((Int*)o2) : NEQDouble((Double*)o2);}

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

    virtual Constant* ToNegative() { return new Double(-d);}
    virtual Constant* ToInc()      { return new Double(d+1);}
    virtual Constant* ToDec()      { return new Double(d-1);}

    Arithmetic* Add(Arithmetic* o2) { return o2->GetType() == CONST_INT? AddInt((Int*)o2) : AddDouble((Double*)o2);}
    Arithmetic* Sub(Arithmetic* o2) { return o2->GetType() == CONST_INT? AddInt((Int*)o2) : AddDouble((Double*)o2);}
    Arithmetic* Mul(Arithmetic* o2) { return o2->GetType() == CONST_INT? AddInt((Int*)o2) : AddDouble((Double*)o2);}
    Arithmetic* Div(Arithmetic* o2) { return o2->GetType() == CONST_INT? AddInt((Int*)o2) : AddDouble((Double*)o2);}

    Arithmetic* AddInt(Int* o2);
    Arithmetic* SubInt(Int* o2);
    Arithmetic* MulInt(Int* o2);
    Arithmetic* DivInt(Int* o2);
    Arithmetic* AddDouble(Double* o2);
    Arithmetic* SubDouble(Double* o2);
    Arithmetic* MulDouble(Double* o2);
    Arithmetic* DivDouble(Double* o2);

    Bool* GT   ( Arithmetic* o2) { return o2->GetType()==CONST_INT? GTInt((Int*)o2) : GTDouble((Double*)o2);}
    Bool* GTEQ ( Arithmetic* o2) { return o2->GetType()==CONST_INT? GTEQInt((Int*)o2) : GTEQDouble((Double*)o2);}
    Bool* LT   ( Arithmetic* o2) { return o2->GetType()==CONST_INT? LTInt((Int*)o2) : LTDouble((Double*)o2);}
    Bool* LTEQ ( Arithmetic* o2) { return o2->GetType()==CONST_INT? LTEQInt((Int*)o2) : LTEQDouble((Double*)o2);}
    Bool* EQ   ( Arithmetic* o2) { return o2->GetType()==CONST_INT? EQInt((Int*)o2) : EQDouble((Double*)o2);}
    Bool* NEQ  ( Arithmetic* o2) { return o2->GetType()==CONST_INT? NEQInt((Int*)o2) : NEQDouble((Double*)o2);}

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

class Bool : public Constant {
public:
    Bool() : Constant(CONST_BOOL) {}
    Bool(bool _b) : Bool() { b= _b;}

    bool GetBool() { return b;}
    void SetBool(bool _b) { b = _b;}

    Bool And(Bool* o2) { return this->GetBool() && o2->GetBool();}
    Bool Or(Bool* o2) { return this->GetBool() || o2->GetBool();}
    Bool Not() { return !this->GetBool();}
private:
    bool b;
};

class Array : public Constant {
public:
    Array(int _sz) : Constant(CONST_ARRAY) { sz_array = _sz;}

    void AddElement(Constant* _c) { vc.push_back(_c);}
private:
    vector<Constant*> vc;
    int sz_array;
};

#endif
