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
    CONST_STRING,
    CONST_ARRAY,
    CONST_NONE
};

class Constant;
class Arithmetic;
class Array;
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
    virtual void Print() = 0;
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

class Bool : public Constant {
public:
    Bool() : Constant(CONST_BOOL) {}
    Bool(bool _b) : Bool() { b= _b;}

    bool GetBool() { return b;}
    void SetBool(bool _b) { b = _b;}

    Bool* And(Bool* o2) { return new Bool(this->GetBool() && o2->GetBool());}
    Bool* Or(Bool* o2)  { return new Bool(this->GetBool() || o2->GetBool());}
    Bool* Not()         { return new Bool(!this->GetBool());}

    /* Printer */
    void Print() { cout << b;}
private:
    bool b;
};

class Array : public Constant {
public:
    Array(int _sz) : Constant(CONST_ARRAY) { sz_array = _sz;}

    void AddElement(Constant* _c) { vc.push_back(_c);}
    Constant* At(int index)       { return vc[index];}

    /* Printer */
    void Print() {
        cout << "[";
        for (Constant *c : vc) {
            c->Print();
            cout << ", ";
        }
        cout << "]";
    }
private:
    vector<Constant*> vc;
    int sz_array;
};

#endif
