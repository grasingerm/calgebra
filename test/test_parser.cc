#include "scalc.hh"
#include <cassert>
#include <iostream>

using namespace scalc;
using namespace std;

int main() {
  Parser parser;
  TokenQueue infix_queue = parser.exprToInfix("3 + 4");
  assert(infix_queue.size() == 3);
 
  cout << "Tests passed.\n";

  return 0;
}
