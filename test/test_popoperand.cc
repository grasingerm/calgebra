#include "operand.hh"
#include <iostream>
#include <cassert>

using namespace scalc;
using namespace std;

int main() {
  TokenStack token_stack;
  token_stack.emplace(new Operand(3.14));
  token_stack.emplace(new Operand(6.28));
  token_stack.emplace(new Operand(0.11));

  assert(popOperandValue(token_stack) == 0.11);
  assert(popOperandValue(token_stack) == 6.28);
  assert(popOperandValue(token_stack) == 3.14);

  try {
    popOperandValue(token_stack);
    cerr << "This should not be printed!!!!!\n";
  }
  catch (const std::exception& e) {
    cout << "Exception thrown! Good.\n";
    cout << e.what() << '\n';
  }

  cout << "Tests passed.\n";

  return 0;
}
