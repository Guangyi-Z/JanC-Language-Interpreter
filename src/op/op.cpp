#include "op.h"

std::map<OP, int> OpProperty::mOP_Precedence = {
    {OP_INC, 9},   // ++
    {OP_DEC, 9},   // --
    {OP_NOT, 9},   // !

    {OP_MUL, 8},   // *
    {OP_DIV, 8},   // /
    {OP_MOD, 8},   // %

    {OP_ADD, 7},   // +
    {OP_SUB, 7},   // -

    {OP_EQ,     6},// ==
    {OP_NOT_EQ, 6},// !=
    {OP_GT,     6},// >
    {OP_LT,     6},// <
    {OP_GT_EQ,  6},// >=
    {OP_LT_EQ,  6},// <=

    {OP_AND, 5},   // &&
    {OP_OR,  4},   // ||

    {OP_ASSIGN, 3} // =
};

const std::set<OP> OpProperty::Prefix_OP_Set = {
    OP_ADD,
    OP_SUB,
    OP_INC,
    OP_DEC,
    OP_NOT
};
const std::set<OP> OpProperty::Prefix_Assignable_OP_Set = {
    OP_INC,
    OP_DEC
};
/* Suffix_op_set and Binary_op_set must be disjoint set */
const std::set<OP> OpProperty::Suffix_OP_Set = {
    OP_INC,
    OP_DEC
};
const std::set<OP> OpProperty::Binary_OP_Set = {
    OP_ADD,    // +
    OP_SUB,    // -
    OP_MUL,    // *
    OP_DIV,    // /
    OP_MOD,    // %
    OP_ASSIGN, // =

    /* logical */
    OP_AND, // &&
    OP_OR,  // ||

    /* relational */
    OP_EQ,     // ==
    OP_NOT_EQ, // !=
    OP_GT,     // >
    OP_LT,     // <
    OP_GT_EQ,  // >=
    OP_LT_EQ,  // <=
};
