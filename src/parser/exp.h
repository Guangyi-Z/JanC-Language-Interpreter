#ifndef EXP_H
#define EXP_H
#include "lexer/op.h"
#include <utility>

/*
 * operations precedence map
 * larger number for higher precedence
 */
// std::map<OP, int> mOP_Precedence = {
// const std::unordered_map<OP, int> mOP = {
const std::pair<OP, int> OP_Precedence[] {
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

/*
 * operations associativity map
 */
enum ASSOCIATE {
    ASS_LEFT,
    ASS_RIGHT
};
const std::pair<OP, ASSOCIATE> OP_Associativity[] {
    {OP_INC, ASS_LEFT},   // ++
    {OP_DEC, ASS_LEFT},   // --
    {OP_NOT, ASS_LEFT},   // !

    {OP_MUL, ASS_LEFT},   // *
    {OP_DIV, ASS_LEFT},   // /
    {OP_MOD, ASS_LEFT},   // %

    {OP_ADD, ASS_LEFT},   // +
    {OP_SUB, ASS_LEFT},   // -

    {OP_EQ,     ASS_LEFT},// ==
    {OP_NOT_EQ, ASS_LEFT},// !=
    {OP_GT,     ASS_LEFT},// >
    {OP_LT,     ASS_LEFT},// <
    {OP_GT_EQ,  ASS_LEFT},// >=
    {OP_LT_EQ,  ASS_LEFT},// <=

    {OP_AND, ASS_LEFT},   // &&
    {OP_OR,  ASS_LEFT},   // ||

    {OP_ASSIGN, ASS_LEFT} // =
};

#endif
