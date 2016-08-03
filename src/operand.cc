#include "operand.hh"

using namespace scalc;

virtual void Operand::_parse(TokenQueue& postfix_queue, TokenStack& opstack) {
  postfix_queue.push(this);
}

virtual void Operand::_eval(TokenQueue& postfix_queue, TokenStack& token_stack) {
  token_stack.push(this);
}
