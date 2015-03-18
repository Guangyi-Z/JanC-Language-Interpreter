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

#endif
