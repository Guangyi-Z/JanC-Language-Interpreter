#ifndef OP_H
    #define OP_H
#include <vector>

enum OP {
    /* arithmetical */
    OP_ADD,    // +
    OP_SUB,    // -
    OP_MUL,    // *
    OP_DIV,    // /
    OP_MOD,    // %
    OP_ASSIGN, // =
    OP_INC,    // ++
    OP_DEC,    // --
    /* logical */
    OP_AND, // &&
    OP_OR,  // ||
    OP_NOT, // !
    /* relational */
    OP_EQ,     // ==
    OP_NOT_EQ, // !=
    OP_GT,     // >
    OP_LT,     // <
    OP_GT_EQ,  // >=
    OP_LT_EQ,  // <=
    /* helper */
    OP_NUMBER_OF_OP,
    OP_NONE
};

const char OP_Char_Set[] = "+-*/%=&|!><";

/*
 * Action Table for the lexer of operations
 */
/* Action Table Entry */
class OPEntry {
public:
    static const char EMPTY_OP = '\0';
    OPEntry (char _c = EMPTY_OP, OP _op = OP_NONE, std::vector<int> _nxt = {}) : c(_c), op(_op), nxt(_nxt) {};
    char c;
    OP op;
    std::vector<int> nxt;
};
/* Action Table */
const OPEntry OP_Action_Table[2][OP_NUMBER_OF_OP] = {
    {
        OPEntry('+' , OP_ADD    , {6}) ,
        OPEntry('-' , OP_SUB    , {7}) ,
        OPEntry('*' , OP_MUL    , {})  ,
        OPEntry('/' , OP_DIV    , {})  ,
        OPEntry('%' , OP_MOD    , {})  ,
        OPEntry('&' , OP_NONE   , {0}) ,
        OPEntry('|' , OP_NONE   , {1}) ,
        OPEntry('!' , OP_NOT    , {3}) ,
        OPEntry('=' , OP_ASSIGN , {2}) ,
        OPEntry('>' , OP_GT     , {4}) ,
        OPEntry('<' , OP_LT     , {5})
    },
    {
        // 0th
        OPEntry('&' , OP_AND    , {}) , // &&
        OPEntry('|' , OP_OR     , {}) , // ||
        OPEntry('=' , OP_ASSIGN , {}) , // ==
        OPEntry('=' , OP_NOT_EQ , {}) , // !=
        OPEntry('=' , OP_GT     , {}) , // >=
        // 5th
        OPEntry('=' , OP_LT  , {})    , // <=
        OPEntry('+' , OP_INC , {})    , // ++
        OPEntry('-' , OP_DEC , {})      // --
    }
};

#endif
