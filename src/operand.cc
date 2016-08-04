#include "operand.hh"

using namespace scalc;

void Operand::_parse(TokenQueue& postfix_queue, TokenStack&) const {
  postfix_queue.emplace(this);
}

void Operand::_eval(TokenQueue&, TokenStack& token_stack) const {
  token_stack.emplace(this);
}

double popOperandValue(TokenStack& token_stack, const char* what_for) 
  throw (std::logic_error) {
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
