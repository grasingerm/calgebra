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

  cout << "Tests passed.\n";

  return 0;
}
