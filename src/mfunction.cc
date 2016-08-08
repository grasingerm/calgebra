#include "mfunction.hh"
#include "monomial.hh"
#include "operand.hh"
#include <stdexcept>

namespace scalc {

void MFunction::_parse(TokenQueue&, TokenStack& opstack) const {
  opstack.emplace(new MFunction(*this));
}

void MFunction::_eval(TokenQueue&, TokenStack& token_stack) const {
  monomial value0 = popOperandValue(token_stack, this->functionName.c_str());

  if (value0.x != 0.0) 
    throw std::runtime_error("Cannot perform a nonlinear function on a "
                             "monomial");

  auto result = this->f(value0.c);
  token_stack.emplace(new Operand(result));
}

}
