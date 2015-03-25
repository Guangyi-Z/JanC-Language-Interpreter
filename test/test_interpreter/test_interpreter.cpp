#include "gtest/gtest.h"
#include "semantic/controller.h"
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
    InterpreterController intr("../test/test_interpreter/interpreter_test1.txt");
    stringstream ss;
    auto buf = cout.rdbuf();
    cout.rdbuf(ss.rdbuf());

    intr.NextStatement();
    intr.NextStatement();
    EXPECT_EQ(">> 1\n>> 2.5\n", ss.str());
    cout.rdbuf(buf);
}

TEST(test_interpreter, exp_with_no_ref) {
    InterpreterController intr("../test/test_interpreter/interpreter_test2.txt");
    stringstream ss;
    auto buf = cout.rdbuf();
    cout.rdbuf(ss.rdbuf());

    intr.NextStatement();
    intr.NextStatement();
    EXPECT_EQ(">> 6\n>> 15.1\n", ss.str());
    cout.rdbuf(buf);
}

TEST(test_interpreter, var) {
    InterpreterController intr("../test/test_interpreter/interpreter_test3.txt");

    intr.NextStatement();
    EXPECT_EQ(1, intr.GetSymbolReader().ReadVarInt("a"));
    intr.NextStatement();
    EXPECT_EQ(2.5, intr.GetSymbolReader().ReadVarDouble("b"));
}

TEST(test_interpreter, array) {
    InterpreterController intr("../test/test_interpreter/interpreter_test4.txt");

    intr.NextStatement();
    EXPECT_EQ(vector<int>({1,2,3,4,5}), intr.GetSymbolReader().ReadArrayInt("arr_a"));
    EXPECT_EQ(5, intr.GetSymbolReader().ReadArraySize("arr_a"));
    intr.NextStatement();
    EXPECT_EQ(vector<double>({1.1,2.2,3.3}), intr.GetSymbolReader().ReadArrayDouble("arr_b"));
    EXPECT_EQ(5, intr.GetSymbolReader().ReadArraySize("arr_b"));
}

TEST(test_interpreter, assgiment) {
    InterpreterController intr("../test/test_interpreter/interpreter_test5.txt");

    stringstream ss;
    auto buf = cout.rdbuf();
    cout.rdbuf(ss.rdbuf());

    intr.NextStatement();
    EXPECT_EQ(1, intr.GetSymbolReader().ReadVarInt("a"));
    intr.NextStatement();
    EXPECT_EQ(2.5, intr.GetSymbolReader().ReadVarDouble("b"));

    intr.NextStatement();
    EXPECT_EQ(2, intr.GetSymbolReader().ReadVarInt("a"));
    intr.NextStatement();
    EXPECT_EQ(3.5, intr.GetSymbolReader().ReadVarDouble("b"));

    EXPECT_EQ(">> 2\n>> 3.5\n", ss.str());
    cout.rdbuf(buf);
}

TEST(test_interpreter, exp_with_ref) {
    InterpreterController intr("../test/test_interpreter/interpreter_test6.txt");
    stringstream ss;
    auto buf = cout.rdbuf();
    cout.rdbuf(ss.rdbuf());

    intr.Continue();
    EXPECT_EQ(">> 2\n>> 1.5\n>> 6.5\n", ss.str());
    cout.rdbuf(buf);
}

TEST(test_interpreter, block) {
    InterpreterController intr("../test/test_interpreter/interpreter_test7.txt");

    intr.NextStatement();
    EXPECT_EQ(1, intr.GetSymbolReader().ReadVarInt("x"));
    intr.NextStatement();
    EXPECT_EQ(2.5, intr.GetSymbolReader().ReadVarDouble("y"));
    // enter block
    intr.NextStatement();
    EXPECT_EQ(1.5, intr.GetSymbolReader().ReadVarDouble("x"));
    EXPECT_EQ(2.5, intr.GetSymbolReader().ReadVarDouble("y"));
}

// TEST(test_symbol_table, function_local_var_override) {
//     InterpreterController intr("../test/test_interpreter/interpreter_test7.txt");
//     stringstream ss;
//     auto buf = cout.rdbuf();
//     cout.rdbuf(ss.rdbuf());
//
//     intr.Continue();
//     EXPECT_EQ(">> 2\n>> 1.5\n>> 6.5", ss.str());
//     cout.rdbuf(buf);
// }

// TEST(test_symbol_table, function_recursion) {
//     InterpreterController intr("../test/test_interpreter/interpreter_test7.txt");
//     stringstream ss;
//     auto buf = cout.rdbuf();
//     cout.rdbuf(ss.rdbuf());
//
//     intr.Continue();
//     EXPECT_EQ(">> 2\n>> 1.5\n>> 6.5", ss.str());
//     cout.rdbuf(buf);
// }
