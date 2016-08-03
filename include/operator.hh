#ifndef __OPERATOR_HH
#define __OPERATOR_HH

#include "token.hh"

namespace scalc {

enum class Associativity { LEFT, RIGHT };

class AbstractOperator : public AbstractToken {
private:
  int precedence;
  Associativity associativity;
  virtual void _parse(TokenQueue&, TokenStack&) const;
  virtual void _eval(TokenQueue&, TokenStack&) const; 
public:
  virtual ~AbstractOperator() {}
  inline auto getPrecedence() { return precedence; }
  inline auto getAssociativity() { return associativity; }
};

} // namespace scalc

#endif // __OPERATOR_HH
