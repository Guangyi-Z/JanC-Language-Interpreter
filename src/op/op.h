#ifndef OP_H
    #define OP_H
#include <vector>
#include <unordered_set>
#include <set>
#include <map>

enum OP {
    /* arithmetical */
    OP_ADD,    // +
    OP_SUB,    // -
    OP_MUL,    // *
    OP_DIV,    // /
    OP_MOD,    // %
    OP_ASSIGN, // = 5th
    OP_INC,    // ++
    OP_DEC,    // --
    /* logical */
    OP_AND, // &&
    OP_OR,  // ||
    OP_NOT, // !    10th
    /* relational */
    OP_EQ,     // ==
    OP_NOT_EQ, // !=
    OP_GT,     // >
    OP_LT,     // <
    OP_GT_EQ,  // >=    15th
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
        OPEntry('&' , OP_AND    , { }) , // &&
        OPEntry('|' , OP_OR     , { }) , // ||
        OPEntry('=' , OP_EQ     , { }) , // ==
        OPEntry('=' , OP_NOT_EQ , { }) , // !=
        OPEntry('=' , OP_GT_EQ  , { }) , // >=
        // 5th
        OPEntry('=' , OP_LT_EQ , {})   , // <=
        OPEntry('+' , OP_INC   , {})   , // ++
        OPEntry('-' , OP_DEC   , {})     // --
    }
};

/*
 * operations precedence map
 * larger number for higher precedence
 */
// std::map<OP, int> mOP_Precedence = {
// const std::unordered_map<OP, int> mOP = {
// const std::pair<OP, int> OP_Precedence[] {
//     {OP_INC, 9},   // ++
//     {OP_DEC, 9},   // --
//     {OP_NOT, 9},   // !
//
//     {OP_MUL, 8},   // *
//     {OP_DIV, 8},   // /
//     {OP_MOD, 8},   // %
//
//     {OP_ADD, 7},   // +
//     {OP_SUB, 7},   // -
//
//     {OP_EQ,     6},// ==
//     {OP_NOT_EQ, 6},// !=
//     {OP_GT,     6},// >
//     {OP_LT,     6},// <
//     {OP_GT_EQ,  6},// >=
//     {OP_LT_EQ,  6},// <=
//
//     {OP_AND, 5},   // &&
//     {OP_OR,  4},   // ||
//
//     {OP_ASSIGN, 3} // =
// };

class OpProperty {
public:
    /* return -1 if non-exist */
    static int GetOPPrecedence(OP op) {
        if (mOP_Precedence.find(op) == mOP_Precedence.end())
            return OP_NOT_EXIST;
        else return mOP_Precedence[op];
    }
    static bool IsPrefixOP(OP op) {
        return Prefix_OP_Set.find(op) != Prefix_OP_Set.end();
    }
    static bool IsPrefixAssignableOP(OP op) {
        return Prefix_Assignable_OP_Set.find(op) != Prefix_Assignable_OP_Set.end();
    }
    static bool IsSuffixOP(OP op) {
        return Suffix_OP_Set.find(op) != Suffix_OP_Set.end();
    }
    static bool IsBinaryOP(OP op) {
        return Binary_OP_Set.find(op) != Binary_OP_Set.end();
    }

    static const int OP_NOT_EXIST = -1;

private:
    OpProperty() {}
    static std::map<OP, int> mOP_Precedence;
    static const std::set<OP> Prefix_OP_Set;
    static const std::set<OP> Prefix_Assignable_OP_Set;
    /* Suffix_op_set and Binary_op_set must be disjoint set */
    static const std::set<OP> Suffix_OP_Set;
    static const std::set<OP> Binary_OP_Set;
};


#endif
