
enum CONST_T {
    CONST_INT,
    CONST_DOUBLE,
    CONST_CHAR,
    CONST_STRING,
    CONST_BOOL
};

class Constant {
public:
    Constant(CONST_T _t): type(_t) {}

    CONST_T GetType() {return type};

private:
    CONST_T type;
};

