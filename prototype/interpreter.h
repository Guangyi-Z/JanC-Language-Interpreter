#include "statement.h"

class Interpreter {
public:
    void IntrStatement(Statement *st) {
        st->Interprete(&sym, &fsym);
    }
private:
    SymbolTable sym;
    FuncTable fsym;
};
