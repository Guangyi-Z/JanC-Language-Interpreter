#include "gtest/gtest.h"
#include "semantic/Interpreter.h"
#include <iostream>
#include <sstream>
#include <vector>
using std::cout;
using std::endl;
using std::stringstream;
using std::string;
using std::vector;

/*
 * Test Case
 */
TEST(test_interpreter, exp_with_no_op) {
    Interpreter intr("../test/test_interpreter/interpreter_test1.txt");
    stringstream ss;
    auto buf = cout.rdbuf();
    cout.rdbuf(ss.rdbuf());

    intr.IntrStatement();
    intr.IntrStatement();
    EXPECT_EQ(">> 1\n>> 2.5\n", ss.str());
    cout.rdbuf(buf);
}

TEST(test_interpreter, exp_with_no_ref) {
    Interpreter intr("../test/test_interpreter/interpreter_test2.txt");
    stringstream ss;
    auto buf = cout.rdbuf();
    cout.rdbuf(ss.rdbuf());

    intr.IntrStatement();
    intr.IntrStatement();
    EXPECT_EQ(">> 6\n>> 15.1\n", ss.str());
    cout.rdbuf(buf);
}

TEST(test_interpreter, var) {
    Interpreter intr("../test/test_interpreter/interpreter_test3.txt");

    intr.IntrStatement();
    EXPECT_EQ(1, intr.ReadVarInt("a"));
    intr.IntrStatement();
    EXPECT_EQ(2.5, intr.ReadVarDouble("b"));
}

TEST(test_interpreter, array) {
    Interpreter intr("../test/test_interpreter/interpreter_test4.txt");

    intr.IntrStatement();
    EXPECT_EQ(vector<int>({1,2,3,4,5}), intr.ReadArrayInt("arr_a"));
    EXPECT_EQ(5, intr.ReadArraySize("arr_a"));
    intr.IntrStatement();
    EXPECT_EQ(vector<double>({1.1,2.2,3.3}), intr.ReadArrayDouble("arr_b"));
    EXPECT_EQ(5, intr.ReadArraySize("arr_b"));
}

TEST(test_interpreter, assgiment) {
    Interpreter intr("../test/test_interpreter/interpreter_test5.txt");

    stringstream ss;
    auto buf = cout.rdbuf();
    cout.rdbuf(ss.rdbuf());

    intr.IntrStatement();
    EXPECT_EQ(1, intr.ReadVarInt("a"));
    intr.IntrStatement();
    EXPECT_EQ(2.5, intr.ReadVarDouble("b"));

    intr.IntrStatement();
    EXPECT_EQ(2, intr.ReadVarInt("a"));
    intr.IntrStatement();
    EXPECT_EQ(3.5, intr.ReadVarDouble("b"));

    EXPECT_EQ(">> 2\n>> 3.5\n", ss.str());
    cout.rdbuf(buf);
}

// TEST(test_symbol_table, assgiment_in_expression) {
// }
// TEST(test_symbol_table, symbol_array) {
// }
// TEST(test_symbol_table, function_invoke) {
// }
