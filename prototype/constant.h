
enum CONST_T {
    CONST_INT,
    CONST_DOUBLE,
    CONST_CHAR,
    CONST_STRING,
    CONST_BOOL,
    CONST_ARRAY
};

class Constant {
public:
    Constant(CONST_T _t): type(_t) {}

    CONST_T GetType() {return type};

private:
    CONST_T type;
};

class Array : public Constant {
public:
    Array() : Constant(CONST_ARRAY) {}

    void AddElement(Constant* _c) { vc.push_back(_c);}
private:
    vector<Constant*> vc;
    int sz_array;
};

