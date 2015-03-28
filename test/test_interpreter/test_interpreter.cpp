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

/*******************
 * Test Expression
 */
TEST(test_expression, exp_with_no_op) {
    InterpreterController intr("../test/test_interpreter/interpreter_test1.txt");
    stringstream ss;
    auto buf = cout.rdbuf();
    cout.rdbuf(ss.rdbuf());

    intr.NextStatement();
    intr.NextStatement();
    EXPECT_EQ("1\n2.5\n", ss.str());
    cout.rdbuf(buf);
}

TEST(test_expression, exp_with_no_ref) {
    InterpreterController intr("../test/test_interpreter/interpreter_test2.txt");
    stringstream ss;
    auto buf = cout.rdbuf();
    cout.rdbuf(ss.rdbuf());

    intr.NextStatement();
    intr.NextStatement();
    EXPECT_EQ("6\n15.1\n", ss.str());
    cout.rdbuf(buf);
}

TEST(test_expression, assgiment) {
    InterpreterController intr("../test/test_interpreter/interpreter_test5.txt");

    stringstream ss;
    auto buf = cout.rdbuf();
    cout.rdbuf(ss.rdbuf());

    intr.Continue();
    EXPECT_EQ("1\n2.5\n2\n3.5\n", ss.str());
    cout.rdbuf(buf);
}

TEST(test_interpreter, exp_with_ref) {
    InterpreterController intr("../test/test_interpreter/interpreter_test6.txt");
    stringstream ss;
    auto buf = cout.rdbuf();
    cout.rdbuf(ss.rdbuf());

    intr.Continue();
    EXPECT_EQ("2\n2.5\n2.5\n1.5\n6.5\n", ss.str());
    cout.rdbuf(buf);
}

TEST(test_interpreter, string_exp) {
    InterpreterController intr("../test/test_interpreter/interpreter_test13.txt");
    stringstream ss;
    auto buf = cout.rdbuf();
    cout.rdbuf(ss.rdbuf());

    intr.Continue();
    EXPECT_EQ("\"hello\"\n\"hello\"\n\"hello world\"\n\"hello world world\"\n\"s2\"\n", ss.str());
    cout.rdbuf(buf);
}

TEST(test_expression, logic) {
    InterpreterController intr("../test/test_interpreter/interpreter_test14.txt");

    stringstream ss;
    auto buf = cout.rdbuf();
    cout.rdbuf(ss.rdbuf());

    intr.Continue();
    EXPECT_EQ("1\n3\n", ss.str());
    cout.rdbuf(buf);
}

TEST(test_expression, unary_op) {
    InterpreterController intr("../test/test_interpreter/interpreter_test15.txt");

    stringstream ss;
    auto buf = cout.rdbuf();
    cout.rdbuf(ss.rdbuf());

    intr.Continue();
    EXPECT_EQ("2\n2\n-3\n3\nfalse\n", ss.str());
    cout.rdbuf(buf);
}

/*******************
 * Test Var
 */
TEST(test_var, var) {
    InterpreterController intr("../test/test_interpreter/interpreter_test3.txt");
    stringstream ss;
    auto buf = cout.rdbuf();
    cout.rdbuf(ss.rdbuf());

    intr.Continue();
    EXPECT_EQ("1\n2.5\n", ss.str());
    cout.rdbuf(buf);
}

TEST(test_var, array) {
    InterpreterController intr("../test/test_interpreter/interpreter_test4.txt");
    stringstream ss;
    auto buf = cout.rdbuf();
    cout.rdbuf(ss.rdbuf());

    intr.Continue();
    EXPECT_EQ("[1, 2, 3, 4, 5, ]\n"
              "[1.1, 2.2, 3.3, 0, 0, ]\n"
              "4.4\n"
              "[1.1, 2.2, 3.3, 4.4, 0, ]\n"
              "[true, 1, 2.5, \"hello world\", ]\n", ss.str());
    cout.rdbuf(buf);
}

TEST(test_var, array_len) {
    InterpreterController intr("../test/test_interpreter/interpreter_test16.txt");
    stringstream ss;
    auto buf = cout.rdbuf();
    cout.rdbuf(ss.rdbuf());

    intr.Continue();
    EXPECT_EQ("5\n4\n", ss.str());
    cout.rdbuf(buf);
}

/*******************
 * Test Structure
 */
TEST(test_structure, block) {
    InterpreterController intr("../test/test_interpreter/interpreter_test7.txt");
    stringstream ss;
    auto buf = cout.rdbuf();
    cout.rdbuf(ss.rdbuf());

    intr.Continue();
    EXPECT_EQ("1\n2.5\n1.5\n1.5\n1.5\n2.5\n", ss.str());
    cout.rdbuf(buf);
}

TEST(test_structure, ifs) {
    InterpreterController intr("../test/test_interpreter/interpreter_test11.txt");
    stringstream ss;
    auto buf = cout.rdbuf();
    cout.rdbuf(ss.rdbuf());

    intr.Continue();
    EXPECT_EQ("6\n8\n7\n", ss.str());
    cout.rdbuf(buf);
}

TEST(test_structure, while_statement) {
    InterpreterController intr("../test/test_interpreter/interpreter_test12.txt");
    stringstream ss;
    auto buf = cout.rdbuf();
    cout.rdbuf(ss.rdbuf());

    intr.Continue();
    EXPECT_EQ("1\n2\n3\n1\n2\n3\n1\n2\n3\n", ss.str());
    cout.rdbuf(buf);
}

/*******************
 * Test Function
 */
TEST(test_function, function_no_arg) {
    InterpreterController intr("../test/test_interpreter/interpreter_test8.txt");
    stringstream ss;
    auto buf = cout.rdbuf();
    cout.rdbuf(ss.rdbuf());

    intr.Continue();
    EXPECT_EQ("1\n5\n2\n", ss.str());
    cout.rdbuf(buf);
}

TEST(test_function, function_with_arg) {
    InterpreterController intr("../test/test_interpreter/interpreter_test17.txt");
    stringstream ss;
    auto buf = cout.rdbuf();
    cout.rdbuf(ss.rdbuf());

    intr.Continue();
    string stest = "3\n5.7\n\"hello world\"\n";
    EXPECT_EQ(stest, ss.str());
    cout.rdbuf(buf);
}

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
//
// TEST(test_interpreter, array_len) {
//     InterpreterController intr("../test/test_interpreter/interpreter_test10.txt");
//     stringstream ss;
//     auto buf = cout.rdbuf();
//     cout.rdbuf(ss.rdbuf());
//
//     intr.NextStatement();
//     intr.NextStatement();
//     intr.NextStatement();
//     intr.NextStatement();
//     EXPECT_EQ("[1, 2, 3, 0, 0, ]\n5\n[1, 2, 3, 4, 0, ]", ss.str());
//     cout.rdbuf(buf);
// }

