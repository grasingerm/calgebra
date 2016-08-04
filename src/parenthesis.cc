#include "parenthesis.hh"
#include "mfunction.hh"
#include <stdexcept>

using namespace scalc;

void LeftParen::_parse(TokenQueue&, TokenStack& opstack) const {
  opstack.emplace(this);
}

void LeftParen::_eval(TokenQueue&, TokenStack&) const {
  throw std::logic_error("Parenthesis should not be evaluated");
}

void RightParen::_parse(TokenQueue& postfix_queue, TokenStack& opstack) const {
  // Find matching left parenthesis
  while (!opstack.empty() && !isTokenLeftParen(opstack.top().get())) {
    postfix_queue.emplace(opstack.top());
    opstack.pop();
  }

  // Check balance of parenthesis
  if (opstack.empty()) throw std::logic_error("Mismatched parenthesis");
  opstack.pop();

  // Check to see if these parenthesis are for a function call
  if (!opstack.empty() && isTokenFunction(opstack.top().get())) {
    postfix_queue.emplace(opstack.top());
    opstack.pop();
  }
}

void RightParen::_eval(TokenQueue&, TokenStack&) const {
  throw std::logic_error("Parenthesis should not be evaluated");
}
