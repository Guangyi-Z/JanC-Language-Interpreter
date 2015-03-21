#ifndef CONSTANT
#define CONSTANT
#include <string>
#include <vector>
using std::string;
using std::vector;

enum CONST_T {
    CONST_INT,
    CONST_DOUBLE,
    CONST_CHAR,
    CONST_STRING,
    CONST_ARRAY_INT,
    CONST_ARRAY_DOUBLE,
    CONST_NONE
};

class Constant {
public:
    Constant ()                   { SetType(CONST_NONE);}
    Constant (int _v)             { SetValue(_v);}
    Constant (double _v)          { SetValue(_v);}
    Constant (char _v)            { SetValue(_v);}
    Constant (string _v)         { SetValue(_v);}
    Constant (vector<int> _v, int _sz)    { SetValue(_v, _sz);}
    Constant (vector<double> _v, int _sz) { SetValue(_v, _sz);}

    void SetValue (int _v)             { SetType(CONST_INT); val.i = _v;}
    void SetValue (double _v)          { SetType(CONST_DOUBLE); val.d = _v;}
    void SetValue (char _v)            { SetType(CONST_CHAR); val.c = _v;}
    void SetValue (string _v)         { SetType(CONST_STRING); val.s = new string(_v);}
    void SetValue (vector<int> _v, int _sz)    { SetType(CONST_ARRAY_INT); val.vi = new vector<int>(_v); sz = _sz;}
    void SetValue (vector<double> _v, int _sz) { SetType(CONST_ARRAY_DOUBLE); val.vd = new vector<double>(_v); sz = _sz;}

    CONST_T GetType()               { return type;}
    int GetInt()                    { return val.i;}
    double GetDouble()              { return val.d;}
    char GetChar()                  { return val.c;}
    string GetString()              { return string(*(string*)(val.s));}
    vector<int> GetArrayInt()       { return (*(vector<int>*)(val.vi));}
    vector<double> GetArrayDouble() { return (*(vector<double>*)(val.vd));}
    int GetArraySize()              { return sz;}

private:
    void SetType  (CONST_T t)          { type = t;}

    CONST_T type;
    union v {
        int i;
        double d;
        char c;
        void *s;    // string *s;
        void *vi;   // vector<int> *vi;
        void *vd;   // vector<double> *vd;
    } val;
    int sz; // for array
};
#endif
