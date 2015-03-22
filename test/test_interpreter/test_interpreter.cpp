#include "gtest/gtest.h"
#include "semantic/Interpreter.h"
#include <iostream>
#include <sstream>
using std::cout;
using std::endl;
using std::stringstream;
using std::string;

/*
 * Test Case
 */
TEST(test_interpreter, var_assgiment) {
    Interpreter intr("../test/test_interpreter/interpreter_test1.txt");

    intr.NextStatement();
    EXPECT_EQ(1, intr.ReadVarInt("a"));
    intr.NextStatement();
    EXPECT_EQ(2.5, intr.ReadVarDouble("b"));
    // intr.NextStatement();
    // EXPECT_EQ(2, intr.ReadVarInt("a"));
    // intr.NextStatement();
    // EXPECT_EQ(3.5, intr.ReadVarDouble("b"));
}

TEST(test_interpreter, array_assgiment) {
    Interpreter intr("../test/test_interpreter/interpreter_test2.txt");

    intr.Continue();
    EXPECT_EQ(1, intr.ReadVarInt("a"));
    EXPECT_EQ(2.5, intr.ReadVarDouble("b"));
}
// TEST(test_symbol_table, assgiment_in_expression) {
// }
// TEST(test_symbol_table, symbol_array) {
// }
// TEST(test_symbol_table, function_invoke) {
// }
