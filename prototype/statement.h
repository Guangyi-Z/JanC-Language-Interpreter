
enum ST_T {
    ST_EMPTY,
    ST_BLOCK,
    ST_FUNC,
    ST_VAR,
    ST_ARRAY
};

class Statement {
public:
    Statement(ST_T _t) : type(_t) {}

    ST_T GetType() { return type;}
    virtual void Interprete(SymbolTable *sym, FuncTable *fsym) = 0;

private:
    ST_T type;
};

class Block : public Statement {
    ;
};

class Func : public Statement {
};

class Var : public Statement {
    ;
};

class Array : public Statement {
    ;
};

class Expression : public Statement {
    void Interprete(SymbolTable *sym, FuncTable *fsym) {
        ;
    }
}

class Return : public Statement {
    ;
};

class If : public Statement {
    ;
};

class While : public Statement {
    ;
};

