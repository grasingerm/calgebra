#include "mfunction.hh"
#include "operand.hh"

namespace scalc {

void MFunction::_parse(TokenQueue&, TokenStack& opstack) const {
  opstack.emplace(new MFunction(*this));
}

void MFunction::_eval(TokenQueue&, TokenStack& token_stack) const {
  auto value0 = popOperandValue(token_stack, this->functionName.c_str());

  auto result = this->f(value0);
  token_stack.emplace(new Operand(result));
}

}
