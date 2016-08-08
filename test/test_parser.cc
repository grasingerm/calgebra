#include "scalc.hh"
#include <cassert>
#include <cmath>
#include <iostream>

using namespace scalc;
using namespace std;

int main() {
  Parser parser;

  cout << "\nTESTING Parser::exprToInfix(const char* expr)\n";
  cout << "=============================================\n\n";

  cout << "Testing expr: 3 + 4\n";
  TokenQueue infix_queue = parser.exprToInfix("3 + 4");
  assert(infix_queue.size() == 3);
  assert(dynamic_cast<const Operand*>(infix_queue.front().get()));
  infix_queue.pop();
  assert(dynamic_cast<const Addition*>(infix_queue.front().get()));
  infix_queue.pop();
  assert(dynamic_cast<const Operand*>(infix_queue.front().get()));
  infix_queue.pop();
  assert(infix_queue.empty());

  cout << "Testing expr: 3+4\n";
  infix_queue = parser.exprToInfix("3+4");
  assert(infix_queue.size() == 3);
  assert(dynamic_cast<const Operand*>(infix_queue.front().get()));
  infix_queue.pop();
  assert(dynamic_cast<const Addition*>(infix_queue.front().get()));
  infix_queue.pop();
  assert(dynamic_cast<const Operand*>(infix_queue.front().get()));
  infix_queue.pop();
  assert(infix_queue.empty());

  cout << "Testing expr: 3+4 * (11 - 1)\n";
  infix_queue = parser.exprToInfix("3+4 * (11 - 1)");
  assert(infix_queue.size() == 9);
  assert(dynamic_cast<const Operand*>(infix_queue.front().get()));
  infix_queue.pop();
  assert(dynamic_cast<const Addition*>(infix_queue.front().get()));
  infix_queue.pop();
  assert(dynamic_cast<const Operand*>(infix_queue.front().get()));
  infix_queue.pop();
  assert(dynamic_cast<const Multiplication*>(infix_queue.front().get()));
  infix_queue.pop();
  assert(dynamic_cast<const LeftParen*>(infix_queue.front().get()));
  infix_queue.pop();
  assert(dynamic_cast<const Operand*>(infix_queue.front().get()));
  infix_queue.pop();
  assert(dynamic_cast<const Subtraction*>(infix_queue.front().get()));
  infix_queue.pop();
  assert(dynamic_cast<const Operand*>(infix_queue.front().get()));
  infix_queue.pop();
  assert(dynamic_cast<const RightParen*>(infix_queue.front().get()));
  infix_queue.pop();
  assert(infix_queue.empty());

  cout << "Testing expr: log(3+4) * (11 - 1)\n";
  infix_queue = parser.exprToInfix("log(3+4) * (11 - 1)");
  cout << "infix_queue.size() = " << infix_queue.size() << '\n';
  cout << *(dynamic_cast<const MFunction*>(infix_queue.front().get())) << '\n';
  assert(infix_queue.size() == 12);
  assert(dynamic_cast<const MFunction*>(infix_queue.front().get()));
  infix_queue.pop();
  cout << *(dynamic_cast<const LeftParen*>(infix_queue.front().get())) << '\n';
  assert(dynamic_cast<const LeftParen*>(infix_queue.front().get()));
  infix_queue.pop();
  cout << *(dynamic_cast<const Operand*>(infix_queue.front().get())) << '\n';
  assert(dynamic_cast<const Operand*>(infix_queue.front().get()));
  infix_queue.pop();
  cout << *(dynamic_cast<const Addition*>(infix_queue.front().get())) << '\n';
  assert(dynamic_cast<const Addition*>(infix_queue.front().get()));
  infix_queue.pop();
  cout << *(dynamic_cast<const Operand*>(infix_queue.front().get())) << '\n';
  assert(dynamic_cast<const Operand*>(infix_queue.front().get()));
  infix_queue.pop();
  cout << *(dynamic_cast<const RightParen*>(infix_queue.front().get())) << '\n';
  assert(dynamic_cast<const RightParen*>(infix_queue.front().get()));
  infix_queue.pop();
  cout << *(dynamic_cast<const Multiplication*>(infix_queue.front().get())) << '\n';
  assert(dynamic_cast<const Multiplication*>(infix_queue.front().get()));
  infix_queue.pop();
  cout << *(dynamic_cast<const LeftParen*>(infix_queue.front().get())) << '\n';
  assert(dynamic_cast<const LeftParen*>(infix_queue.front().get()));
  infix_queue.pop();
  cout << *(dynamic_cast<const Operand*>(infix_queue.front().get())) << '\n';
  assert(dynamic_cast<const Operand*>(infix_queue.front().get()));
  infix_queue.pop();
  cout << *(dynamic_cast<const Subtraction*>(infix_queue.front().get())) << '\n';
  assert(dynamic_cast<const Subtraction*>(infix_queue.front().get()));
  infix_queue.pop();
  cout << *(dynamic_cast<const Operand*>(infix_queue.front().get())) << '\n';
  assert(dynamic_cast<const Operand*>(infix_queue.front().get()));
  infix_queue.pop();
  cout << *(dynamic_cast<const RightParen*>(infix_queue.front().get())) << '\n';
  assert(dynamic_cast<const RightParen*>(infix_queue.front().get()));
  infix_queue.pop();
  assert(infix_queue.empty());

  cout << "Testing expr: 3 + 4 * 2 / (1 - 5) ^ 2 ^ 3\n";
  infix_queue = parser.exprToInfix("3 + 4 * 2 / (1 - 5) ^ 2 ^ 3");
  cout << "infix_queue.size() = " << infix_queue.size() << '\n';
  cout << *(dynamic_cast<const Operand*>(infix_queue.front().get())) << '\n';
  assert(infix_queue.size() == 15);
  assert(dynamic_cast<const Operand*>(infix_queue.front().get()));
  infix_queue.pop();
  cout << *(dynamic_cast<const Addition*>(infix_queue.front().get())) << '\n';
  assert(dynamic_cast<const Addition*>(infix_queue.front().get()));
  infix_queue.pop();
  cout << *(dynamic_cast<const Operand*>(infix_queue.front().get())) << '\n';
  assert(dynamic_cast<const Operand*>(infix_queue.front().get()));
  infix_queue.pop();
  cout << *(dynamic_cast<const Multiplication*>(infix_queue.front().get())) << '\n';
  assert(dynamic_cast<const Multiplication*>(infix_queue.front().get()));
  infix_queue.pop();
  cout << *(dynamic_cast<const Operand*>(infix_queue.front().get())) << '\n';
  assert(dynamic_cast<const Operand*>(infix_queue.front().get()));
  infix_queue.pop();
  cout << *(dynamic_cast<const Division*>(infix_queue.front().get())) << '\n';
  assert(dynamic_cast<const Division*>(infix_queue.front().get()));
  infix_queue.pop();
  cout << *(dynamic_cast<const LeftParen*>(infix_queue.front().get())) << '\n';
  assert(dynamic_cast<const LeftParen*>(infix_queue.front().get()));
  infix_queue.pop();
  cout << *(dynamic_cast<const Operand*>(infix_queue.front().get())) << '\n';
  assert(dynamic_cast<const Operand*>(infix_queue.front().get()));
  infix_queue.pop();
  cout << *(dynamic_cast<const Subtraction*>(infix_queue.front().get())) << '\n';
  assert(dynamic_cast<const Subtraction*>(infix_queue.front().get()));
  infix_queue.pop();
  cout << *(dynamic_cast<const Operand*>(infix_queue.front().get())) << '\n';
  assert(dynamic_cast<const Operand*>(infix_queue.front().get()));
  infix_queue.pop();
  cout << *(dynamic_cast<const RightParen*>(infix_queue.front().get())) << '\n';
  assert(dynamic_cast<const RightParen*>(infix_queue.front().get()));
  infix_queue.pop();
  cout << *(dynamic_cast<const Carrot*>(infix_queue.front().get())) << '\n';
  assert(dynamic_cast<const Carrot*>(infix_queue.front().get()));
  infix_queue.pop();
  cout << *(dynamic_cast<const Operand*>(infix_queue.front().get())) << '\n';
  assert(dynamic_cast<const Operand*>(infix_queue.front().get()));
  infix_queue.pop();
  cout << *(dynamic_cast<const Carrot*>(infix_queue.front().get())) << '\n';
  assert(dynamic_cast<const Carrot*>(infix_queue.front().get()));
  infix_queue.pop();
  cout << *(dynamic_cast<const Operand*>(infix_queue.front().get())) << '\n';
  assert(dynamic_cast<const Operand*>(infix_queue.front().get()));
  infix_queue.pop();
  assert(infix_queue.empty());

  cout << "\nTESTING Parser::infixToPostfix(TokenQueue&)\n";
  cout << "=============================================\n\n";
  infix_queue = parser.exprToInfix("3 + 4 * 2 / (1 - 5) ^ 2 ^ 3");
  cout << "infix_queue.size() = " << infix_queue.size() << '\n';
  TokenQueue postfix_queue = parser.infixToPostfix(infix_queue);
  cout << "postfix_queue.size() = " << postfix_queue.size() << '\n';
  cout << *(dynamic_cast<const Operand*>(postfix_queue.front().get())) << '\n';
  assert(postfix_queue.size() == 13);
  assert(dynamic_cast<const Operand*>(postfix_queue.front().get()));
  postfix_queue.pop();
  cout << *(dynamic_cast<const Operand*>(postfix_queue.front().get())) << '\n';
  assert(dynamic_cast<const Operand*>(postfix_queue.front().get()));
  postfix_queue.pop();
  cout << *(dynamic_cast<const Operand*>(postfix_queue.front().get())) << '\n';
  assert(dynamic_cast<const Operand*>(postfix_queue.front().get()));
  postfix_queue.pop();
  cout << *(dynamic_cast<const Multiplication*>(postfix_queue.front().get())) << '\n';
  assert(dynamic_cast<const Multiplication*>(postfix_queue.front().get()));
  postfix_queue.pop();
  cout << *(dynamic_cast<const Operand*>(postfix_queue.front().get())) << '\n';
  assert(dynamic_cast<const Operand*>(postfix_queue.front().get()));
  postfix_queue.pop();
  cout << *(dynamic_cast<const Operand*>(postfix_queue.front().get())) << '\n';
  assert(dynamic_cast<const Operand*>(postfix_queue.front().get()));
  postfix_queue.pop();
  cout << *(dynamic_cast<const Subtraction*>(postfix_queue.front().get())) << '\n';
  assert(dynamic_cast<const Subtraction*>(postfix_queue.front().get()));
  postfix_queue.pop();
  cout << *(dynamic_cast<const Operand*>(postfix_queue.front().get())) << '\n';
  assert(dynamic_cast<const Operand*>(postfix_queue.front().get()));
  postfix_queue.pop();
  cout << *(dynamic_cast<const Operand*>(postfix_queue.front().get())) << '\n';
  assert(dynamic_cast<const Operand*>(postfix_queue.front().get()));
  postfix_queue.pop();
  cout << *(dynamic_cast<const Carrot*>(postfix_queue.front().get())) << '\n';
  assert(dynamic_cast<const Carrot*>(postfix_queue.front().get()));
  postfix_queue.pop();
  cout << *(dynamic_cast<const Carrot*>(postfix_queue.front().get())) << '\n';
  assert(dynamic_cast<const Carrot*>(postfix_queue.front().get()));
  postfix_queue.pop();
  cout << *(dynamic_cast<const Division*>(postfix_queue.front().get())) << '\n';
  assert(dynamic_cast<const Division*>(postfix_queue.front().get()));
  postfix_queue.pop();
  cout << *(dynamic_cast<const Addition*>(postfix_queue.front().get())) << '\n';
  assert(dynamic_cast<const Addition*>(postfix_queue.front().get()));
  postfix_queue.pop();
  assert(postfix_queue.empty());

  infix_queue = parser.exprToInfix("sin(cos(3.14) / 3 * 3.1415)");
  cout << "infix_queue.size() = " << infix_queue.size() << '\n';
  postfix_queue = parser.infixToPostfix(infix_queue);
  cout << "postfix_queue.size() = " << postfix_queue.size() << '\n';
  cout << *(dynamic_cast<const Operand*>(postfix_queue.front().get())) << '\n';
  assert(postfix_queue.size() == 7);
  assert(dynamic_cast<const Operand*>(postfix_queue.front().get()));
  assert(dynamic_cast<const Operand*>(postfix_queue.front().get())->getValue() == 3.14);
  postfix_queue.pop();
  cout << *(dynamic_cast<const MFunction*>(postfix_queue.front().get())) << '\n';
  assert(dynamic_cast<const MFunction*>(postfix_queue.front().get()));
  postfix_queue.pop();
  cout << *(dynamic_cast<const Operand*>(postfix_queue.front().get())) << '\n';
  assert(dynamic_cast<const Operand*>(postfix_queue.front().get())->getValue() == 3);
  assert(dynamic_cast<const Operand*>(postfix_queue.front().get()));
  postfix_queue.pop();
  cout << *(dynamic_cast<const Division*>(postfix_queue.front().get())) << '\n';
  assert(dynamic_cast<const Division*>(postfix_queue.front().get()));
  postfix_queue.pop();
  cout << *(dynamic_cast<const Operand*>(postfix_queue.front().get())) << '\n';
  assert(dynamic_cast<const Operand*>(postfix_queue.front().get())->getValue() == 3.1415);
  assert(dynamic_cast<const Operand*>(postfix_queue.front().get()));
  postfix_queue.pop();
  cout << *(dynamic_cast<const Multiplication*>(postfix_queue.front().get())) << '\n';
  assert(dynamic_cast<const Multiplication*>(postfix_queue.front().get()));
  postfix_queue.pop();
  cout << *(dynamic_cast<const MFunction*>(postfix_queue.front().get())) << '\n';
  assert(dynamic_cast<const MFunction*>(postfix_queue.front().get()));
  postfix_queue.pop();
  assert(postfix_queue.empty());

  cout << "\nTESTING Parser::valueEvaluateExpr(const char*)\n";
  cout << "=============================================\n\n";
  const double eps = 1e-7;
  cout << "3 + 4 * 2 / (1 - 5) ^ 2 ^ 3 = " << parser.valueEvaluateExpr("3 + 4 * 2 / (1 - 5) ^ 2 ^ 3") << '\n';
  assert(abs((3.0001220703125 - parser.valueEvaluateExpr("3 + 4 * 2 / (1 - 5) ^ 2 ^ 3")).c) < eps);
  cout << "3 + 0 * 2 = " << parser.valueEvaluateExpr("3 + 0 * 2") << '\n';
  assert(abs((3.0 - parser.valueEvaluateExpr("3 + 0 * 2")).c) < eps);
  cout << "log(exp(1.0)) = " << parser.valueEvaluateExpr("log(exp(1.0))") << '\n';
  assert(abs((1.0 - parser.valueEvaluateExpr("log(exp(1.0))")).c) < eps);
  assert(abs((-0.8660092970238366 - parser.valueEvaluateExpr("sin(cos(3.14) / 3 * 3.1415)")).c) < eps);
  assert(abs((4.0 - parser.valueEvaluateExpr("-(0.1 - 4.1)")).c) < eps);
  assert(abs((4.2 - parser.valueEvaluateExpr("-(-0.1 - 4.1)")).c) < eps);
  cout << "(3+(4-1))*5 = " << parser.valueEvaluateExpr("(3+(4-1))*5") << '\n';
  assert(abs((30.0 - parser.valueEvaluateExpr("(3+(4-1))*5")).c) < eps);
  cout << "(3+(4-1))5 = " << parser.valueEvaluateExpr("(3+(4-1))5") << '\n';
  assert(abs((30.0 - parser.valueEvaluateExpr("(3+(4-1))5")).c) < eps);
  cout << "(3+(4-1)) 5 = " << parser.valueEvaluateExpr("(3+(4-1)) 5") << '\n';
  assert(abs((30.0 - parser.valueEvaluateExpr("(3+(4-1)) 5")).c) < eps);
  cout << "5(3+(4-1)) = " << parser.valueEvaluateExpr("5(3+(4-1))") << '\n';
  assert(abs((30.0 - parser.valueEvaluateExpr("5(3+(4-1))")).c) < eps);
  cout << "5 (3+(4-1)) = " << parser.valueEvaluateExpr("5 (3+(4-1))") << '\n';
  assert(abs((30.0 - parser.valueEvaluateExpr("5 (3+(4-1))")).c) < eps);
  cout << '\n';
  try {
    cout << "Evaluating \n";
    parser.valueEvaluateExpr("  ");
    cerr << "This should not be printed!!!!!\n";
    assert(false);
  }
  catch (const std::exception& e) {
    cout << "Exception thrown! Good.\n";
    cout << e.what() << '\n';
  }
  try {
    cout << "Evaluating 3 * (4 -5  \n";
    parser.valueEvaluateExpr("3 * (4 -5  ");
    cerr << "This should not be printed!!!!!\n";
    assert(false);
  }
  catch (const std::exception& e) {
    cout << "Exception thrown! Good.\n";
    cout << e.what() << '\n';
  }
  try {
    cout << "Evaluating 3 4 -5  \n";
    parser.valueEvaluateExpr("3 4 -5  ");
    cerr << "This should not be printed!!!!!\n";
    assert(false);
  }
  catch (const std::exception& e) {
    cout << "Exception thrown! Good.\n";
    cout << e.what() << '\n';
  }
  try {
    cout << "Evaluating sint(3.4)\n";
    parser.valueEvaluateExpr("sint(3.4)");
    cerr << "This should not be printed!!!!!\n";
    assert(false);
  }
  catch (const std::exception& e) {
    cout << "Exception thrown! Good.\n";
    cout << e.what() << '\n';
  }
  try {
    cout << "Evaluating (4 -)\n";
    parser.valueEvaluateExpr("(4 -)");
    cerr << "This should not be printed!!!!!\n";
    assert(false);
  }
  catch (const std::exception& e) {
    cout << "Exception thrown! Good.\n";
    cout << e.what() << '\n';
  }
  try {
    cout << "Evaluating ()\n";
    parser.valueEvaluateExpr("()");
    cerr << "This should not be printed!!!!!\n";
    assert(false);
  }
  catch (const std::exception& e) {
    cout << "Exception thrown! Good.\n";
    cout << e.what() << '\n';
  }
  try {
    cout << "Evaluating 3 + + 4\n";
    parser.valueEvaluateExpr("3 + + 4");
    cerr << "This should not be printed!!!!!\n";
    assert(false);
  }
  catch (const std::exception& e) {
    cout << "Exception thrown! Good.\n";
    cout << e.what() << '\n';
  }
  try {
    cout << "Evaluating 3 + 4 *\n";
    parser.valueEvaluateExpr("3 + 4 *");
    cerr << "This should not be printed!!!!!\n";
    assert(false);
  }
  catch (const std::exception& e) {
    cout << "Exception thrown! Good.\n";
    cout << e.what() << '\n';
  }

  cout << "\nTESTING Parser::formatEvaluateExpr(const char*) in solver mode\n";
  cout << "=============================================\n\n";
  parser.setMode(ParserMode::LINEAR_EQ_SOLVER);
  cout << "Solving 3x + 5 = 1\n";
  cout << parser.formatEvaluateExpr("3x + 5 = 1") << '\n';
  assert(aeq(-0.75, parser.valueEvaluateExpr("3x + 5 = 1")));
  cout << '\n';
  cout << "Solving 3x = 1\n";
  cout << parser.formatEvaluateExpr("3x = 1") << '\n';
  assert(aeq(1.0 / 3.0, parser.valueEvaluateExpr("3x = 1")));
  cout << '\n';
  cout << "Solving x - 1 = (1 - 11)\n";
  cout << parser.formatEvaluateExpr("x - 1 = (1 - 11)") << '\n';
  assert(aeq(-9.0, parser.valueEvaluateExpr("x - 1 = (1 - 11)")));
  cout << '\n';
  cout << "Solving 3(x - 1) = 3(1 - 11)\n";
  cout << parser.formatEvaluateExpr("3(x - 1) = 3(1 - 11)") << '\n';
  assert(aeq(-9.0, parser.valueEvaluateExpr("3(x - 1) = 3(1 - 11)")));
  cout << '\n';
  cout << "Solving -(x + 1) = 3(1 - 11) ^ 2\n";
  cout << parser.formatEvaluateExpr("-(x + 1) = 3(1 - 11) ^ 2") << '\n';
  assert(aeq(-301.0, parser.valueEvaluateExpr("-(x + 1) = 3(1 - 11) ^ 2")));
  cout << '\n';
  cout << "Solving 2 * x + 0.5 = 1\n";
  cout << parser.formatEvaluateExpr("2 * x + 0.5 = 1") << '\n';
  assert(aeq(0.25, parser.valueEvaluateExpr("2 * x + 0.5 = 1")));
  cout << '\n';
  cout << "Solving 2x + 1 = 2(1-x)\n";
  cout << parser.formatEvaluateExpr("2x + 1 = 2(1-x)") << '\n';
  assert(aeq(0.25, parser.valueEvaluateExpr("2x + 1 = 2(1-x)")));
  cout << '\n';

  try {
    cout << "Solving 3 + 4 = 2\n";
    parser.valueEvaluateExpr("3 + 4 = 2");
    cerr << "This should not be printed!!!!!\n";
    assert(false);
  }
  catch (const std::exception& e) {
    cout << e.what() << '\n';
  }
  try {
    cout << "Solving 3x + 4 = (2x + x)\n";
    parser.valueEvaluateExpr("3x + 4 = (2x + x)");
    cerr << "This should not be printed!!!!!\n";
    assert(false);
  }
  catch (const std::exception& e) {
    cout << e.what() << '\n';
  }
  try {
    cout << "Solving sin(x) = (2x + x)\n";
    parser.valueEvaluateExpr("sin(x) = (2x + x)");
    cerr << "This should not be printed!!!!!\n";
    assert(false);
  }
  catch (const std::exception& e) {
    cout << e.what() << '\n';
  }
  try {
    cout << "Solving (x)*x = (2x + x)\n";
    parser.valueEvaluateExpr("(x)*x = (2x + x)");
    cerr << "This should not be printed!!!!!\n";
    assert(false);
  }
  catch (const std::exception& e) {
    cout << e.what() << '\n';
  }
    
  cout << "\n\n=============================================\n\n";
  cout << "\nTests passed.\n";

  return 0;
}
