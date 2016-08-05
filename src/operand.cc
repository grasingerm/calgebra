#include "operand.hh"

namespace scalc {

void Operand::_parse(TokenQueue& postfix_queue, TokenStack&) const {
  postfix_queue.emplace(new Operand(*this));
}

void Operand::_eval(TokenQueue&, TokenStack& token_stack) const {
  token_stack.emplace(new Operand(*this));
}

double popOperandValue(TokenStack& token_stack, const char* what_for) {
  char what[256] = "Not enough operands for ";

  const auto ptoken = (!token_stack.empty()) ? 
                      dynamic_cast<const Operand*>(token_stack.top().get()) 
                      : nullptr;
  if (ptoken == nullptr) 
    throw std::logic_error(std::strncat(what, what_for, 224));

  const double retval = ptoken->getValue();
  token_stack.pop();

  return retval;
}

void X::_parse(TokenQueue& postfix_queue, TokenStack&) const {
  postfix_queue.emplace(new X(*this));
}

void X::_eval(TokenQueue&, TokenStack& token_stack) const {
  token_stack.emplace(new X(*this));
}

}
