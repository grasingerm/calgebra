#include "operator.hh"

using namespace scalc;

virtual void 
AbstractOperator::_parse(TokenQueue& postfix_queue, TokenStack& opstack) {
  while (!opstack.empty())
}

virtual void Operand::_eval(TokenQueue& postfix_queue, TokenStack& token_stack) {
  token_stack.push(this);
}
