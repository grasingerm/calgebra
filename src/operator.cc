#include "operator.hh"
#include "operand.hh"
#include <stdexcept>
#include <cmath>

namespace scalc {

int getTokenPrecedence(const AbstractToken* ptoken) {
  const AbstractOperator* poperator;
  if ( (poperator = dynamic_cast<const AbstractOperator*>(ptoken)) )
    return poperator->getPrecedence();

  throw std::logic_error("Non-operator found where operator was expected");
}

void 
AbstractOperator::_parse(TokenQueue& postfix_queue, TokenStack& opstack) const {
  while (!opstack.empty() && 
         dynamic_cast<const AbstractOperator*>(opstack.top().get()) != nullptr && 
         ((this->associativity == Associativity::LEFT && 
           this->precedence <= getTokenPrecedence(opstack.top().get())) ||
          this->precedence < getTokenPrecedence(opstack.top().get())))
  {
    postfix_queue.emplace(opstack.top());
    opstack.pop();
  }
  this->_pushToTokenStack(opstack);
}

void Carrot::_eval(TokenQueue&, TokenStack& token_stack) const {
  auto value0 = popOperandValue(token_stack, "'^' operator");
  auto value1 = popOperandValue(token_stack, "'^' operator");

  if (value0.x != 0.0 || value1.x != 0.0)
    throw std::runtime_error("Cannot perform exponentiation with a monomial");

  monomial result { 0.0, std::pow(value1.c, value0.c) };
  token_stack.emplace(new Operand(result));
}

void Negation::_eval(TokenQueue&, TokenStack& token_stack) const {
  auto value0 = popOperandValue(token_stack, "unary '-' operator");

  auto result = -value0;
  token_stack.emplace(new Operand(result));
}

void Multiplication::_eval(TokenQueue&, TokenStack& token_stack) const {
  auto value0 = popOperandValue(token_stack, "'*' operator");
  auto value1 = popOperandValue(token_stack, "'*' operator");

  auto result = value1 * value0;
  token_stack.emplace(new Operand(result));
}

void Division::_eval(TokenQueue&, TokenStack& token_stack) const {
  auto value0 = popOperandValue(token_stack, "'/' operator");
  auto value1 = popOperandValue(token_stack, "'/' operator");

  auto result = value1 / value0;
  token_stack.emplace(new Operand(result));
}

void Addition::_eval(TokenQueue&, TokenStack& token_stack) const {
  auto value0 = popOperandValue(token_stack, "'+' operator");
  auto value1 = popOperandValue(token_stack, "'+' operator");

  auto result = value1 + value0;
  token_stack.emplace(new Operand(result));
}

void Subtraction::_eval(TokenQueue&, TokenStack& token_stack) const {
  auto value0 = popOperandValue(token_stack, "'-' operator");
  auto value1 = popOperandValue(token_stack, "'-' operator");

  auto result = value1 - value0;
  token_stack.emplace(new Operand(result));
}

TokenHandler Multiplication::getInverse() const { 
  return TokenHandler(new Division()); 
}

TokenHandler Division::getInverse() const { 
  return TokenHandler(new Multiplication()); 
}

TokenHandler Addition::getInverse() const { 
  return TokenHandler(new Subtraction()); 
}

TokenHandler Subtraction::getInverse() const { 
  return TokenHandler(new Addition()); 
}

}
