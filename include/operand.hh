#ifndef __OPERAND_HH
#define __OPERAND_HH

#include "token.hh"
#include <cstring>

namespace scalc {

class Operand : public AbstractToken {
private:
  double value;
  virtual void _parse(TokenQueue&, TokenStack&) const;
  virtual void _eval(TokenQueue&, TokenStack&) const; 
public:
  Operand(const double value) : value(value) {}
  virtual ~Operand() {}
  inline auto getValue() const noexcept { return value; }
};

double popOperandValue(TokenStack& token_stack, const char* what_for="operator");

} // namespace scalc

#endif // __OPERAND_HH
