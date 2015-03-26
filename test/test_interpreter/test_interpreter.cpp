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
    EXPECT_EQ("1\n2.5\n", ss.str());
    cout.rdbuf(buf);
}

TEST(test_interpreter, exp_with_no_ref) {
    InterpreterController intr("../test/test_interpreter/interpreter_test2.txt");
    stringstream ss;
    auto buf = cout.rdbuf();
    cout.rdbuf(ss.rdbuf());

    intr.NextStatement();
    intr.NextStatement();
    EXPECT_EQ("6\n15.1\n", ss.str());
    cout.rdbuf(buf);
}

TEST(test_interpreter, var) {
    InterpreterController intr("../test/test_interpreter/interpreter_test3.txt");
    stringstream ss;
    auto buf = cout.rdbuf();
    cout.rdbuf(ss.rdbuf());

    intr.Continue();
    EXPECT_EQ("1\n2.5\n", ss.str());
    cout.rdbuf(buf);
}

TEST(test_interpreter, array) {
    InterpreterController intr("../test/test_interpreter/interpreter_test4.txt");
    stringstream ss;
    auto buf = cout.rdbuf();
    cout.rdbuf(ss.rdbuf());

    intr.Continue();
    // var arr_c[3] = {true, 1,2.5,"hello world"};
    // arr_c;
    // intr.NextStatement();
    // intr.NextStatement();
    // EXPECT_EQ("[1, 2, 3, 4, 5, ]\n[1.1, 2.2, 3.3, ]\n[true, 1, 2.5, \"hello world\", ]", ss.str());
    EXPECT_EQ("[1, 2, 3, 4, 5, ]\n[1.1, 2.2, 3.3, ]\n", ss.str());
    cout.rdbuf(buf);
}

TEST(test_interpreter, assgiment) {
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

TEST(test_interpreter, block) {
    InterpreterController intr("../test/test_interpreter/interpreter_test7.txt");
    stringstream ss;
    auto buf = cout.rdbuf();
    cout.rdbuf(ss.rdbuf());

    intr.Continue();
    EXPECT_EQ("1\n2.5\n1.5\n1.5\n1.5\n2.5\n", ss.str());
    cout.rdbuf(buf);
}

TEST(test_interpreter, function_no_arg) {
    InterpreterController intr("../test/test_interpreter/interpreter_test8.txt");
    stringstream ss;
    auto buf = cout.rdbuf();
    cout.rdbuf(ss.rdbuf());

    intr.Continue();
    EXPECT_EQ("1\n5\n", ss.str());
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

